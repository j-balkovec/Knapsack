"""
@file_name: parser.py

@author: Jakob Balkovec
@date: December 2024

@description: This file parses the test_log log file and finds the ideal parameters ACO & SA algorithms.

@bugs: <NONE>
"""

from parser_utils import (LogEntry,
                          parse_log_file,
                          clean_entries)

TEST_LOG_FILE_PATH: str = r'/Users/jbalkovec/Desktop/Knapsack/Logs/test_log.log'

# Simulated Annealing
entries = clean_entries(parse_log_file(TEST_LOG_FILE_PATH))

print(sorted(entries, key=lambda x: x.solution, reverse=True))