#!/usr/bin/env python3

import subprocess
import random
import sys
import signal
import json
import csv
from collections import deque, defaultdict
from multiprocessing import Pool, cpu_count
from datetime import datetime
import time
import statistics
import os
import glob

# ANSI color codes
class Colors:
    GREEN = '\033[92m'
    YELLOW = '\033[93m'
    RED = '\033[91m'
    BLUE = '\033[94m'
    CYAN = '\033[96m'
    MAGENTA = '\033[95m'
    RESET = '\033[0m'
    BOLD = '\033[1m'

# 42 School official benchmarks
BENCHMARKS = {
    3: {'5': 3, '4': 3, '3': 3, '2': 3, '1': 3},
    5: {'5': 12, '4': 12, '3': 12, '2': 12, '1': 12},
    100: {'5': 700, '4': 900, '3': 1100, '2': 1300, '1': 1500},
    500: {'5': 5500, '4': 7000, '3': 8500, '2': 10000, '1': 11500}
}

class PatternGenerator:
    """Generate specific test patterns"""
    
    @staticmethod
    def sorted_list(size):
        """Already sorted"""
        return list(range(size))
    
    @staticmethod
    def reverse_sorted(size):
        """Reverse sorted - classic worst case"""
        return list(range(size-1, -1, -1))
    
    @staticmethod
    def rotated_sorted(size, rotation=None):
        """Sorted but rotated"""
        lst = list(range(size))
        rotation = rotation or random.randint(1, size-1)
        return lst[rotation:] + lst[:rotation]
    
    @staticmethod
    def nearly_sorted(size, swaps=2):
        """Almost sorted with few elements out of place"""
        lst = list(range(size))
        for _ in range(swaps):
            i, j = random.sample(range(size), 2)
            lst[i], lst[j] = lst[j], lst[i]
        return lst
    
    @staticmethod
    def alternating(size):
        """Alternating high-low pattern"""
        lst = list(range(size))
        result = []
        low, high = 0, size - 1
        while low <= high:
            result.append(lst[high])
            high -= 1
            if low <= high:
                result.append(lst[low])
                low += 1
        return result
    
    @staticmethod
    def v_shaped(size):
        """Descending then ascending"""
        mid = size // 2
        return list(range(mid, -1, -1)) + list(range(mid+1, size))
    
    @staticmethod
    def chunked(size, num_chunks=4):
        """Groups of sorted segments"""
        lst = list(range(size))
        random.shuffle(lst)
        chunk_size = size // num_chunks
        result = []
        for i in range(num_chunks):
            start = i * chunk_size
            end = start + chunk_size if i < num_chunks - 1 else size
            chunk = lst[start:end]
            chunk.sort()
            result.extend(chunk)
        return result
    
    @staticmethod
    def random_list(size):
        """Random permutation"""
        return random.sample(range(size), size)


class PushSwapTester:
    def __init__(self, sizes, num_workers=None, iterations=100, export_files=False, optimize=False, bonus=False):
        self.sizes = sizes if isinstance(sizes, list) else [sizes]
        self.num_workers = num_workers or cpu_count()
        self.iterations = iterations
        self.export_files = export_files
        self.optimize = optimize
        self.bonus = bonus
        self.results = defaultdict(lambda: {
            'tests': [],
            'ok_count': 0,
            'ko_count': 0,
            'timeout_count': 0,
            'crash_count': 0,
            'worst_case': None,
            'best_case': None
        })
        self.shutdown_requested = False
        
        signal.signal(signal.SIGINT, self.signal_handler)
        signal.signal(signal.SIGTERM, self.signal_handler)
    
    def signal_handler(self, signum, frame):
        if not self.shutdown_requested:
            print(f"\n\n{Colors.YELLOW}[!] Shutdown requested... finishing current batch{Colors.RESET}")
            self.shutdown_requested = True
        else:
            print(f"\n\n{Colors.RED}[X] Force quit{Colors.RESET}")
            sys.exit(1)
    
    def get_grade(self, size, steps):
        """Get performance grade based on benchmarks"""
        if size not in BENCHMARKS:
            return "N/A", Colors.RESET, 0
        
        bench = BENCHMARKS[size]
        
        if steps <= bench['5']:
            return "5/5", Colors.GREEN, 5
        elif steps <= bench['4']:
            return "4/5", Colors.CYAN, 4
        elif steps <= bench['3']:
            return "3/5", Colors.YELLOW, 3
        elif steps <= bench['2']:
            return "2/5", Colors.YELLOW, 2
        elif steps <= bench['1']:
            return "1/5", Colors.RED, 1
        else:
            return "0/5", Colors.RED, 0
    
    def print_progress_bar(self, current, total, prefix='', length=40):
        """Print a progress bar"""
        percent = current / total
        filled = int(length * percent)
        bar = '█' * filled + '░' * (length - filled)
        print(f'\r{prefix} |{bar}| {current}/{total} ({percent*100:.1f}%)', end='', flush=True)
    
    def generate_test_suite(self, size):
        """Generate comprehensive test suite for a given size"""
        tests = []
        
        # Pattern-based tests (20 of each)
        patterns = [
            ('sorted', PatternGenerator.sorted_list),
            ('reverse', PatternGenerator.reverse_sorted),
            ('rotated', PatternGenerator.rotated_sorted),
            ('nearly_sorted', PatternGenerator.nearly_sorted),
            ('alternating', PatternGenerator.alternating),
            ('v_shaped', PatternGenerator.v_shaped),
            ('chunked', PatternGenerator.chunked),
        ]
        
        for pattern_name, generator in patterns:
            for _ in range(20):
                tests.append((pattern_name, generator(size)))
        
        # Random tests - more if not optimizing (since no mutation phase)
        random_count = 140 if self.optimize else 860
        for _ in range(random_count):
            tests.append(('random', PatternGenerator.random_list(size)))
        
        return tests
    
    def mutate_list(self, numbers):
        """Create variations to find worse cases"""
        mutations = []
        
        for _ in range(10):
            mutated = numbers.copy()
            i, j = random.sample(range(len(mutated)), 2)
            mutated[i], mutated[j] = mutated[j], mutated[i]
            mutations.append(mutated)
        
        for _ in range(5):
            mutated = numbers.copy()
            i = random.randint(0, len(mutated) - 2)
            j = random.randint(i + 1, len(mutated))
            mutated[i:j] = reversed(mutated[i:j])
            mutations.append(mutated)
        
        for shift in [1, -1, len(numbers)//4, -len(numbers)//4]:
            mutated = numbers.copy()
            d = deque(mutated)
            d.rotate(shift)
            mutations.append(list(d))
        
        return mutations
    
    def test_bonus_checker(self, numbers, instructions, expected_output):
        """Test the bonus checker program"""
        try:
            args = ['./checker'] + [str(n) for n in numbers]
            result = subprocess.run(
                args,
                input=instructions,
                capture_output=True,
                text=True,
                timeout=5
            )
            
            stdout = result.stdout.strip()
            stderr = result.stderr.strip()
            
            # Check if output matches expected
            if expected_output == "OK" and stdout == "OK":
                return True, "OK", None
            elif expected_output == "KO" and stdout == "KO":
                return True, "KO", None
            elif expected_output == "Error" and "Error" in stderr:
                return True, "Error", None
            else:
                return False, stdout if stdout else stderr, f"Expected {expected_output}, got stdout='{stdout}' stderr='{stderr}'"
                
        except subprocess.TimeoutExpired:
            return False, "TIMEOUT", "Program timed out"
        except FileNotFoundError:
            print("Error: ./checker not found in current directory")
            sys.exit(1)
        except Exception as e:
            return False, "ERROR", str(e)
    
    def run_bonus_tests(self):
        """Run comprehensive bonus checker tests"""
        print(f"\n{Colors.BOLD}{'='*70}")
        print(f"BONUS CHECKER TESTS")
        print(f"{'='*70}{Colors.RESET}\n")
        
        tests = []
        passed = 0
        failed = 0
        
        # Test 1: Valid sorting - should return OK
        print(f"{Colors.CYAN}Test 1: Valid sorting (should return OK){Colors.RESET}")
        result, output, error = self.test_bonus_checker(
            [3, 2, 1],
            "sa\nrra\n",
            "OK"
        )
        tests.append(("Valid sorting", result, output, error))
        if result:
            passed += 1
            print(f"{Colors.GREEN}[PASS]{Colors.RESET} Output: {output}")
        else:
            failed += 1
            print(f"{Colors.RED}[FAIL]{Colors.RESET} {error}")
        
        # Test 2: Invalid sorting - should return KO
        print(f"\n{Colors.CYAN}Test 2: Invalid sorting (should return KO){Colors.RESET}")
        result, output, error = self.test_bonus_checker(
            [3, 2, 1],
            "sa\n",
            "KO"
        )
        tests.append(("Invalid sorting", result, output, error))
        if result:
            passed += 1
            print(f"{Colors.GREEN}[PASS]{Colors.RESET} Output: {output}")
        else:
            failed += 1
            print(f"{Colors.RED}[FAIL]{Colors.RESET} {error}")
        
        # Test 3: Invalid instruction - should return Error
        print(f"\n{Colors.CYAN}Test 3: Invalid instruction (should return Error){Colors.RESET}")
        result, output, error = self.test_bonus_checker(
            [3, 2, 1],
            "sa\ninvalid_instruction\npb\n",
            "Error"
        )
        tests.append(("Invalid instruction", result, output, error))
        if result:
            passed += 1
            print(f"{Colors.GREEN}[PASS]{Colors.RESET} Output: {output}")
        else:
            failed += 1
            print(f"{Colors.RED}[FAIL]{Colors.RESET} {error}")
        
        # Test 4: Already sorted - should return OK
        print(f"\n{Colors.CYAN}Test 4: Already sorted with no operations (should return OK){Colors.RESET}")
        result, output, error = self.test_bonus_checker(
            [1, 2, 3],
            "",
            "OK"
        )
        tests.append(("Already sorted", result, output, error))
        if result:
            passed += 1
            print(f"{Colors.GREEN}[PASS]{Colors.RESET} Output: {output}")
        else:
            failed += 1
            print(f"{Colors.RED}[FAIL]{Colors.RESET} {error}")
        
        # Test 5: Invalid arguments - duplicate
        print(f"\n{Colors.CYAN}Test 5: Duplicate arguments (should return Error){Colors.RESET}")
        result, output, error = self.test_bonus_checker(
            [1, 2, 2, 3],
            "sa\n",
            "Error"
        )
        tests.append(("Duplicate arguments", result, output, error))
        if result:
            passed += 1
            print(f"{Colors.GREEN}[PASS]{Colors.RESET} Output: {output}")
        else:
            failed += 1
            print(f"{Colors.RED}[FAIL]{Colors.RESET} {error}")
        
        # Test 6: Complex valid sorting
        print(f"\n{Colors.CYAN}Test 6: Complex valid sorting (should return OK){Colors.RESET}")
        result, output, error = self.test_bonus_checker(
            [29, 4, 26, 17, 16, 21, 37, 48, 14, 33, 20, 15, 8, 39, 22, 49, 25, 47, 24, 40, 23, 43, 46, 3, 7, 50, 19, 35, 28, 41, 12, 18, 42, 38, 2, 1, 5, 31, 32, 6, 36, 44, 10, 30, 9, 11, 45, 13, 34, 27],
            "ra\npb\npb\npb\npb\npb\nra\nra\npb\nra\npb\npb\npb\nra\npb\nra\npb\nra\npb\nra\npb\nra\nra\npb\npb\nra\npb\nra\npb\nra\npb\npb\nra\nra\npb\npb\npb\npb\npb\npb\npb\nra\npb\npb\npb\npb\nra\npb\npb\npb\npb\npb\nra\npb\npb\nra\nra\npb\npb\nra\nra\npb\npb\npb\npb\npb\npb\npb\npb\npb\npb\npa\nra\npa\nra\npa\npa\nrra\nrra\npa\npa\npa\nra\npa\npa\nrra\npa\nrrb\npa\nra\nrrb\npa\nrrb\npa\nrrb\npa\nrrb\nrrb\npa\nra\nra\nra\npa\nrrb\npa\nrrr\nrra\npa\nrrr\npa\nrrr\nrrb\nrrb\nrrb\nrrb\npa\nra\nra\nrrb\npa\nrrr\nrrr\nrrb\nrrb\nrrb\npa\nrrb\npa\nra\nra\nra\nra\nrrb\npa\nrr\nra\nra\npa\nrrr\nrrr\nrrb\nrrb\npa\nra\nra\nra\nrrb\nrrb\npa\nrrb\nrrb\npa\nra\nra\nrrb\npa\nra\nra\nrrb\npa\nrr\nrr\nrr\nrr\nra\npa\nrr\npa\nra\nra\nra\npa\nra\npa\nra\npa\nrra\nrra\npa\nrr\nrr\nrr\nra\nra\npa\nrb\npa\npa\nrr\nra\npa\nrr\npa\npa\nrra\nrra\npa\nrr\nrr\nrr\nra\nra\nra\nra\npa\nrra\npa\nra\nra\npa\nrr\nra\nra\npa\npa\nra\nra\nra\nra\npa\nra\nra\nra\nra\nra\nra\nra\nra\n",
            "OK"
        )
        tests.append(("Complex sorting", result, output, error))
        if result:
            passed += 1
            print(f"{Colors.GREEN}[PASS]{Colors.RESET} Output: {output}")
        else:
            failed += 1
            print(f"{Colors.RED}[FAIL]{Colors.RESET} {error}")
        
        # Test 7: Stack b not empty - should return KO
        print(f"\n{Colors.CYAN}Test 7: Stack b not empty (should return KO){Colors.RESET}")
        result, output, error = self.test_bonus_checker(
            [3, 2, 1],
            "pb\nsa\n",
            "KO"
        )
        tests.append(("Stack b not empty", result, output, error))
        if result:
            passed += 1
            print(f"{Colors.GREEN}[PASS]{Colors.RESET} Output: {output}")
        else:
            failed += 1
            print(f"{Colors.RED}[FAIL]{Colors.RESET} {error}")
        
        # Test 8: Empty instruction list on sorted stack
        print(f"\n{Colors.CYAN}Test 8: No instructions on sorted stack (should return OK){Colors.RESET}")
        result, output, error = self.test_bonus_checker(
            [0, 1, 2, 3, 4],
            "",
            "OK"
        )
        tests.append(("Empty instructions", result, output, error))
        if result:
            passed += 1
            print(f"{Colors.GREEN}[PASS]{Colors.RESET} Output: {output}")
        else:
            failed += 1
            print(f"{Colors.RED}[FAIL]{Colors.RESET} {error}")
        
        # Test 9: Malformed instruction
        print(f"\n{Colors.CYAN}Test 9: Malformed instruction (should return Error){Colors.RESET}")
        result, output, error = self.test_bonus_checker(
            [3, 2, 1],
            "sa\n  pb\nxyz\n",
            "Error"
        )
        tests.append(("Malformed instruction", result, output, error))
        if result:
            passed += 1
            print(f"{Colors.GREEN}[PASS]{Colors.RESET} Output: {output}")
        else:
            failed += 1
            print(f"{Colors.RED}[FAIL]{Colors.RESET} {error}")
        
        # Test 10: All valid operations
        print(f"\n{Colors.CYAN}Test 10: Test all valid operations{Colors.RESET}")
        result, output, error = self.test_bonus_checker(
            [4, 3, 2, 1, 0],
            "pb\npb\nsa\nra\nrra\nrr\nrrr\nss\npa\npa\n",
            "KO"  # This sequence won't sort it
        )
        tests.append(("All operations", result, output, error))
        if result:
            passed += 1
            print(f"{Colors.GREEN}[PASS]{Colors.RESET} Output: {output}")
        else:
            failed += 1
            print(f"{Colors.RED}[FAIL]{Colors.RESET} {error}")
        
        # Summary
        print(f"\n{Colors.BOLD}{'='*70}")
        print(f"BONUS TEST SUMMARY")
        print(f"{'='*70}{Colors.RESET}")
        print(f"Total tests: {len(tests)}")
        print(f"{Colors.GREEN}Passed: {passed}{Colors.RESET}")
        print(f"{Colors.RED}Failed: {failed}{Colors.RESET}")
        
        if failed > 0:
            print(f"\n{Colors.RED}Failed tests:{Colors.RESET}")
            for name, result, output, error in tests:
                if not result:
                    print(f"  - {name}: {error}")
        
        return passed == len(tests)
    
    def analyze_results(self, size):
        """Comprehensive statistical analysis"""
        data = self.results[size]
        if not data['tests']:
            return None
        
        steps = [t['steps'] for t in data['tests'] if t['steps'] is not None]
        if not steps:
            return None
        
        return {
            'count': len(steps),
            'min': min(steps),
            'max': max(steps),
            'mean': statistics.mean(steps),
            'median': statistics.median(steps),
            'stdev': statistics.stdev(steps) if len(steps) > 1 else 0,
            'p90': statistics.quantiles(steps, n=10)[8] if len(steps) >= 10 else max(steps),
            'p95': statistics.quantiles(steps, n=20)[18] if len(steps) >= 20 else max(steps),
            'p99': statistics.quantiles(steps, n=100)[98] if len(steps) >= 100 else max(steps),
        }
    
    def print_results(self, size):
        """Print detailed results for a size"""
        data = self.results[size]
        stats = self.analyze_results(size)
        
        if not stats:
            print(f"\n{Colors.RED}No valid results for size {size}{Colors.RESET}")
            return
        
        print(f"\n{Colors.BOLD}{'='*70}")
        print(f"RESULTS FOR SIZE {size}")
        print(f"{'='*70}{Colors.RESET}")
        
        print(f"\n{Colors.CYAN}Tests Summary:{Colors.RESET}")
        print(f"  Total tests: {len(data['tests'])}")
        print(f"  Valid (OK): {Colors.GREEN}{data['ok_count']}{Colors.RESET}")
        print(f"  Invalid (KO): {Colors.RED}{data['ko_count']}{Colors.RESET}")
        print(f"  Timeouts: {Colors.YELLOW}{data['timeout_count']}{Colors.RESET}")
        print(f"  Crashes: {Colors.RED}{data['crash_count']}{Colors.RESET}")
        
        print(f"\n{Colors.CYAN}Statistical Analysis:{Colors.RESET}")
        print(f"  Mean:     {stats['mean']:.2f} steps")
        print(f"  Median:   {stats['median']:.0f} steps")
        print(f"  Std Dev:  {stats['stdev']:.2f}")
        print(f"  Min:      {Colors.GREEN}{stats['min']}{Colors.RESET} steps")
        print(f"  Max:      {Colors.RED}{stats['max']}{Colors.RESET} steps")
        print(f"  90th %:   {stats['p90']:.0f} steps")
        print(f"  95th %:   {stats['p95']:.0f} steps")
        print(f"  99th %:   {stats['p99']:.0f} steps")
        
        # Benchmark grade
        if size in BENCHMARKS:
            grade, color, points = self.get_grade(size, stats['median'])
            print(f"\n{Colors.CYAN}Performance Grade:{Colors.RESET} {color}{grade}{Colors.RESET}")
            print(f"  (Based on median: {stats['median']:.0f} steps)")
            
            bench = BENCHMARKS[size]
            print(f"\n{Colors.CYAN}42 School Benchmarks:{Colors.RESET}")
            print(f"  {Colors.GREEN}5 points{Colors.RESET}: < {bench['5']}")
            print(f"  {Colors.CYAN}4 points{Colors.RESET}: < {bench['4']}")
            print(f"  {Colors.YELLOW}3 points{Colors.RESET}: < {bench['3']}")
            print(f"  {Colors.YELLOW}2 points{Colors.RESET}: < {bench['2']}")
            print(f"  {Colors.RED}1 point{Colors.RESET}:  < {bench['1']}")
        
        # Pattern analysis
        pattern_stats = defaultdict(list)
        for test in data['tests']:
            if test['steps'] is not None:
                pattern_stats[test['pattern']].append(test['steps'])
        
        if pattern_stats:
            print(f"\n{Colors.CYAN}Performance by Pattern:{Colors.RESET}")
            for pattern, steps in sorted(pattern_stats.items()):
                avg = statistics.mean(steps)
                print(f"  {pattern:15s}: {avg:7.2f} avg steps (n={len(steps)})")
        
        # Worst and best cases
        if data['worst_case']:
            print(f"\n{Colors.RED}Worst Case: {data['worst_case']['steps']} steps{Colors.RESET}")
            print(f"  Pattern: {data['worst_case']['pattern']}")
            print(f"  Numbers: {' '.join(map(str, data['worst_case']['numbers']))}")
        
        if data['best_case']:
            print(f"\n{Colors.GREEN}Best Case: {data['best_case']['steps']} steps{Colors.RESET}")
            print(f"  Pattern: {data['best_case']['pattern']}")
    
    def export_results(self, filename_prefix='push_swap_results'):
        """Export results to JSON and CSV"""
        timestamp = datetime.now().strftime('%Y%m%d_%H%M%S')
        
        # JSON export (detailed)
        json_file = f"{filename_prefix}_{timestamp}.json"
        json_data = {}
        for size, data in self.results.items():
            stats = self.analyze_results(size)
            json_data[size] = {
                'statistics': stats,
                'summary': {
                    'ok_count': data['ok_count'],
                    'ko_count': data['ko_count'],
                    'timeout_count': data['timeout_count'],
                    'crash_count': data['crash_count']
                },
                'worst_case': data['worst_case'],
                'best_case': data['best_case'],
                'all_tests': data['tests']
            }
        
        with open(json_file, 'w') as f:
            json.dump(json_data, f, indent=2)
        
        # CSV export (summary)
        csv_file = f"{filename_prefix}_{timestamp}.csv"
        with open(csv_file, 'w', newline='') as f:
            writer = csv.writer(f)
            writer.writerow(['Size', 'Pattern', 'Steps', 'Valid'])
            for size, data in self.results.items():
                for test in data['tests']:
                    if test['steps'] is not None:
                        writer.writerow([size, test['pattern'], test['steps'], test['valid']])
        
        print(f"\n{Colors.GREEN}[+] Results exported:{Colors.RESET}")
        print(f"  JSON: {json_file}")
        print(f"  CSV:  {csv_file}")
    
    def run(self):
        """Main testing loop"""
        # If bonus mode, only run bonus tests
        if self.bonus:
            self.run_bonus_tests()
            return
        
        print(f"{Colors.BOLD}{'='*70}")
        print(f"PUSH_SWAP COMPREHENSIVE TESTER")
        print(f"{'='*70}{Colors.RESET}")
        print(f"Sizes to test: {', '.join(map(str, self.sizes))}")
        print(f"Worker threads: {self.num_workers}")
        if self.optimize:
            print(f"Mode: Pattern testing (280) + Mutation optimization ({self.iterations} iterations)")
        else:
            print(f"Mode: Extensive pattern testing (1000 tests per size)")
        print(f"Press Ctrl+C to stop (twice to force quit)\n")
        
        pool = None
        try:
            pool = Pool(processes=self.num_workers)
            
            for size in self.sizes:
                if self.shutdown_requested:
                    break
                
                print(f"\n{Colors.BOLD}{Colors.BLUE}{'='*70}")
                print(f"TESTING SIZE: {size}")
                print(f"{'='*70}{Colors.RESET}\n")
                
                # Phase 1: Pattern testing
                total_tests_desc = "280 tests" if self.optimize else "1000 tests"
                print(f"{Colors.CYAN}Phase 1: Pattern-based testing ({total_tests_desc}){Colors.RESET}")
                test_suite = self.generate_test_suite(size)
                
                total_tests = len(test_suite)
                for i in range(0, total_tests, 20):
                    if self.shutdown_requested:
                        break
                    
                    batch = test_suite[i:i+20]
                    self.print_progress_bar(i, total_tests, prefix='Progress')
                    
                    results = pool.map(test_single_list, batch)
                    
                    for (pattern, numbers), (steps, valid, error_type) in zip(batch, results):
                        test_result = {
                            'pattern': pattern,
                            'numbers': numbers,
                            'steps': steps,
                            'valid': valid,
                            'error_type': error_type
                        }
                        self.results[size]['tests'].append(test_result)
                        
                        if valid:
                            self.results[size]['ok_count'] += 1
                        elif error_type == 'timeout':
                            self.results[size]['timeout_count'] += 1
                        elif error_type == 'crash':
                            self.results[size]['crash_count'] += 1
                        else:
                            self.results[size]['ko_count'] += 1
                        
                        if steps is not None:
                            if self.results[size]['worst_case'] is None or steps > self.results[size]['worst_case']['steps']:
                                self.results[size]['worst_case'] = test_result.copy()
                            
                            if self.results[size]['best_case'] is None or steps < self.results[size]['best_case']['steps']:
                                self.results[size]['best_case'] = test_result.copy()
                
                self.print_progress_bar(total_tests, total_tests, prefix='Progress')
                print()  # New line after progress bar
                
                # Phase 2: Worst case optimization (only if optimize flag is set)
                if self.optimize:
                    print(f"\n{Colors.CYAN}Phase 2: Optimizing worst case ({self.iterations} iterations){Colors.RESET}")
                    
                    if self.results[size]['worst_case']:
                        worst_steps = self.results[size]['worst_case']['steps']
                        improvements = 0
                        
                        for iteration in range(self.iterations):
                            if self.shutdown_requested:
                                break
                            
                            self.print_progress_bar(iteration, self.iterations, prefix='Optimization')
                            
                            mutations = self.mutate_list(self.results[size]['worst_case']['numbers'])
                            mutation_tests = [('mutation', m) for m in mutations]
                            results = pool.map(test_single_list, mutation_tests)
                            
                            for (pattern, numbers), (steps, valid, error_type) in zip(mutation_tests, results):
                                if steps is not None and valid:
                                    test_result = {
                                        'pattern': 'mutation',
                                        'numbers': numbers,
                                        'steps': steps,
                                        'valid': valid,
                                        'error_type': error_type
                                    }
                                    self.results[size]['tests'].append(test_result)
                                    self.results[size]['ok_count'] += 1
                                    
                                    if steps > worst_steps:
                                        self.results[size]['worst_case'] = test_result.copy()
                                        worst_steps = steps
                                        improvements += 1
                                        print(f"\n{Colors.MAGENTA}[*] New worst case found: {steps} steps!{Colors.RESET}")
                                        self.print_progress_bar(iteration, self.iterations, prefix='Optimization')
                        
                        self.print_progress_bar(self.iterations, self.iterations, prefix='Optimization')
                        print(f"\n{Colors.GREEN}Found {improvements} improvements{Colors.RESET}")
                else:
                    print(f"\n{Colors.YELLOW}Tip: Use --optimize flag to enable worst-case mutation testing{Colors.RESET}")
                
                # Print results for this size
                self.print_results(size)
        
        except KeyboardInterrupt:
            pass
        
        finally:
            if pool is not None:
                print(f"\n{Colors.YELLOW}🧹 Cleaning up...{Colors.RESET}")
                pool.close()
                pool.join()
            
            # Final summary
            print(f"\n{Colors.BOLD}{'='*70}")
            print(f"FINAL SUMMARY - ALL SIZES")
            print(f"{'='*70}{Colors.RESET}")
            
            for size in self.sizes:
                if self.results[size]['tests']:
                    stats = self.analyze_results(size)
                    grade, color, points = self.get_grade(size, stats['median'])
                    print(f"\nSize {size:3d}: {color}{grade}{Colors.RESET} "
                          f"(median: {stats['median']:.0f}, max: {stats['max']}, "
                          f"tests: {len(self.results[size]['tests'])})")
            
            # Export results if enabled
            if self.export_files:
                self.export_results()
            else:
                print(f"\n{Colors.YELLOW}Tip: Use --export flag to save results to JSON/CSV files{Colors.RESET}")
            
            print(f"\n{Colors.GREEN}Testing complete!{Colors.RESET}\n")


def test_single_list(test_data):
    """Worker function to test a single list"""
    pattern, numbers = test_data
    
    try:
        # Run push_swap
        args = ['./push_swap'] + [str(n) for n in numbers]
        result = subprocess.run(
            args,
            capture_output=True,
            text=True,
            timeout=10
        )
        
        if result.returncode != 0:
            return (None, False, 'crash')
        
        steps_output = result.stdout.strip()
        if not steps_output:
            return (0, True, None)
        
        step_count = len([line for line in steps_output.split('\n') if line.strip()])
        
        # Run checker_linux
        args = ['./checker_linux'] + [str(n) for n in numbers]
        result = subprocess.run(
            args,
            input=steps_output + '\n',
            capture_output=True,
            text=True,
            timeout=10
        )
        
        output = result.stdout.strip().upper()
        is_valid = "OK" in output or (result.returncode == 0 and not result.stderr.strip())
        
        return (step_count, is_valid, None)
        
    except subprocess.TimeoutExpired:
        return (None, False, 'timeout')
    except Exception as e:
        return (None, False, 'crash')


def cleanup_generated_files():
    """Remove all generated test result files"""
    patterns = [
        'push_swap_results_*.json',
        'push_swap_results_*.csv'
    ]
    
    files_found = []
    for pattern in patterns:
        files_found.extend(glob.glob(pattern))
    
    if not files_found:
        print(f"{Colors.YELLOW}No generated files found to clean up.{Colors.RESET}")
        return
    
    print(f"{Colors.CYAN}Found {len(files_found)} file(s) to delete:{Colors.RESET}")
    for f in files_found:
        print(f"  - {f}")
    
    response = input(f"\n{Colors.YELLOW}Delete these files? (y/N): {Colors.RESET}").strip().lower()
    
    if response == 'y':
        deleted = 0
        for f in files_found:
            try:
                os.remove(f)
                deleted += 1
                print(f"{Colors.GREEN}[+]{Colors.RESET} Deleted: {f}")
            except Exception as e:
                print(f"{Colors.RED}[-]{Colors.RESET} Failed to delete {f}: {e}")
        
        print(f"\n{Colors.GREEN}[+] Cleanup complete! Deleted {deleted}/{len(files_found)} files.{Colors.RESET}")
    else:
        print(f"{Colors.YELLOW}Cleanup cancelled.{Colors.RESET}")


def main():
    # Check for cleanup mode first
    if len(sys.argv) == 2 and sys.argv[1] in ['--cleanup', '-c']:
        cleanup_generated_files()
        sys.exit(0)
    
    # Check for bonus mode
    if len(sys.argv) == 2 and sys.argv[1] in ['--bonus', '-b']:
        tester = PushSwapTester([100], bonus=True)
        tester.run()
        sys.exit(0)
    
    if len(sys.argv) < 2:
        print("Usage: python3 tester.py <size1> [size2 size3 ...] [options]")
        print("       python3 tester.py --bonus")
        print("       python3 tester.py --cleanup")
        print("\nOptions:")
        print("  --workers N, -w N       Number of worker threads (default: CPU count)")
        print("  --iterations N, -i N    Number of worst case optimization iterations (default: 100)")
        print("  --optimize, -o          Enable worst-case mutation testing (Phase 2)")
        print("  --export, -e            Export results to JSON and CSV files")
        print("  --bonus, -b             Run bonus checker tests")
        print("  --cleanup, -c           Delete all generated result files")
        print("\nExamples:")
        print("  python3 tester.py 100")
        print("  python3 tester.py 3 5 100 500")
        print("  python3 tester.py 100 --workers 8")
        print("  python3 tester.py 100 --optimize --iterations 500")
        print("  python3 tester.py 100 -w 8 -o -i 200 --export")
        print("  python3 tester.py --bonus")
        print("  python3 tester.py --cleanup")
        print("\nRecommended sizes: 3, 5, 100, 500")
        print("\nNote: Without --optimize, runs 1000 tests. With --optimize, runs 280 + mutation tests.")
        sys.exit(1)
    
    sizes = []
    num_workers = None
    iterations = 100
    export_files = False
    optimize = False
    
    i = 1
    while i < len(sys.argv):
        if sys.argv[i] in ['--workers', '-w']:
            if i + 1 < len(sys.argv):
                try:
                    num_workers = int(sys.argv[i + 1])
                    if num_workers < 1:
                        print("Error: workers must be at least 1")
                        sys.exit(1)
                except ValueError:
                    print(f"Error: '{sys.argv[i + 1]}' is not a valid integer for workers")
                    sys.exit(1)
                i += 2
            else:
                print("Error: --workers requires a number")
                sys.exit(1)
        elif sys.argv[i] in ['--iterations', '-i']:
            if i + 1 < len(sys.argv):
                try:
                    iterations = int(sys.argv[i + 1])
                    if iterations < 1:
                        print("Error: iterations must be at least 1")
                        sys.exit(1)
                except ValueError:
                    print(f"Error: '{sys.argv[i + 1]}' is not a valid integer for iterations")
                    sys.exit(1)
                i += 2
            else:
                print("Error: --iterations requires a number")
                sys.exit(1)
        elif sys.argv[i] in ['--export', '-e']:
            export_files = True
            i += 1
        elif sys.argv[i] in ['--optimize', '-o']:
            optimize = True
            i += 1
        elif sys.argv[i] in ['--bonus', '-b']:
            print("Error: --bonus must be used alone")
            sys.exit(1)
        elif sys.argv[i] in ['--cleanup', '-c']:
            print("Error: --cleanup must be used alone")
            sys.exit(1)
        else:
            try:
                size = int(sys.argv[i])
                if size < 2:
                    print(f"Error: size must be at least 2")
                    sys.exit(1)
                sizes.append(size)
            except ValueError:
                print(f"Error: '{sys.argv[i]}' is not a valid integer")
                sys.exit(1)
            i += 1
    
    if not sizes:
        print("Error: at least one size must be specified")
        sys.exit(1)
    
    tester = PushSwapTester(sizes, num_workers, iterations, export_files, optimize)
    tester.run()


if __name__ == "__main__":
    main()