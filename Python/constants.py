"""
@file_name: constants.py

@author: Jakob Balkovec
@date: December 2024

@description: This file contains the constants used throughout the project.

@bugs: <NONE>
"""

# -------- <input_generator.py> -------- #
LOWER_BOUND_ITEMS = 10
UPPER_BOUND_ITEMS = 50

LOWER_BOUND_CAPACITY = 50
UPPER_BOUND_CAPACITY = 150

BREAK = '\n\n'
MEGA_TAB = '\t\t\t\t\t\t\t'
ITEMS = 'Items'
CAPACITY = 'Capacity'

SIZE_MAP = {
    '1': 1000,
    '2': 5000,
    '3': 10000,
    '4': 50000,
    '5': 100000,
    '6': 500000,
    '7': 1000000,
    '8': 5000000,
    '9': 10000000,
    '10': 50000000,
}

# -------- <shared_with_multiple> -------- #
COLORS: dict = {'red': '\033[91m',
                'green': '\033[92m',
                'yellow': '\033[93m',
                'blue': '\033[94m',
                'magenta': '\033[95m',
                'cyan': '\033[96m',
                'white': '\033[97m',
                'reset': '\033[0m'}

CAPACITY_SIZE = 250
# -------- <input_generator.py> -------- #

# -------- <parser_utils.py, my_parser.py> -------- #
# All current log files
MAIN_LOG_PATH = r'/Users/jbalkovec/Desktop/Knapsack/Logs/main.log'

EXECUTION_TIME_LOG_PATH = r'/Users/jbalkovec/Desktop/Knapsack/Logs/execution_time.log'
MIN_EXECUTION_TIME_LOG_PATH = r'/Users/jbalkovec/Desktop/Knapsack/Logs/min_execution_time.log'

INPUT_GENERATOR_LOG_PATH = r'/Users/jbalkovec/Desktop/Knapsack/Logs/input_generator.log'

UTILITY_LOG_PATH = r'/Users/jbalkovec/Desktop/Knapsack/Logs/utility.log'

PARSER_LOG_PATH = r'/Users/jbalkovec/Desktop/Knapsack/Logs/parser_log.log'

SA_TEST_LOG_PATH = r'/Users/jbalkovec/Desktop/Knapsack/Logs/SA_test.log'
ACO_TEST_LOG_PATH = r'/Users/jbalkovec/Desktop/Knapsack/Logs/ACO_test.log'
TEST_LOG_PATH = r'/Users/jbalkovec/Desktop/Knapsack/Logs/test_log.log'

CLEAR_TEST_LOGS: list = [SA_TEST_LOG_PATH, 
                         ACO_TEST_LOG_PATH, 
                         TEST_LOG_PATH]

CLEAR_EXEC_TIME_LOGS: list = [EXECUTION_TIME_LOG_PATH, 
                              MIN_EXECUTION_TIME_LOG_PATH]

CLEAR_ALL_LOGS: list = [MAIN_LOG_PATH, 
                        EXECUTION_TIME_LOG_PATH, 
                        MIN_EXECUTION_TIME_LOG_PATH, 
                        INPUT_GENERATOR_LOG_PATH, 
                        UTILITY_LOG_PATH, 
                        PARSER_LOG_PATH, 
                        SA_TEST_LOG_PATH, 
                        ACO_TEST_LOG_PATH, 
                        TEST_LOG_PATH]

ACO_DUMP_PATH = r'/Users/jbalkovec/Desktop/Knapsack/Tests/Python/Dump/aco_dump.txt'
SA_DUMP_PATH = r'/Users/jbalkovec/Desktop/Knapsack/Tests/Python/Dump/sa_dump.txt'

CONFIG = {
    "clear_main_log":          False, # clear_log()
    "clear_exec_time_log":     False, # clear_log()
    "clear_min_exec_time_log": False, # clear_log()
    "clear_input_gen_log":     False, # clear_log()
    "clear_utility_log":       False, # clear_log()
    "clear_parser_log":        False, # clear_log()
    "clear_sa_test_log":       False, # clear_log()
    "clear_aco_test_log":      False, # clear_log()
    "clear_test_log":          False, # clear_log()
    "clear_aco_dump":          True, # clear_log()
    "clear_sa_dump":           True, # clear_log()
    "clear_test_logs":         True, # clear_logs()
    "clear_exec_time_logs":    False, # clear_logs()
    "clear_all":               False, # clear_logs()
}

PATHS_CONFIG = {
    "clear_main_log":          MAIN_LOG_PATH,
    "clear_exec_time_log":     EXECUTION_TIME_LOG_PATH,
    "clear_min_exec_time_log": MIN_EXECUTION_TIME_LOG_PATH,
    "clear_input_gen_log":     INPUT_GENERATOR_LOG_PATH,
    "clear_utility_log":       UTILITY_LOG_PATH,
    "clear_parser_log":        PARSER_LOG_PATH,
    "clear_sa_test_log":       SA_TEST_LOG_PATH,
    "clear_aco_test_log":      ACO_TEST_LOG_PATH,
    "clear_test_log":          TEST_LOG_PATH,
    "clear_aco_dump":          ACO_DUMP_PATH,
    "clear_sa_dump":           SA_DUMP_PATH,
    "clear_test_logs":         CLEAR_TEST_LOGS,      # clear_logs()
    "clear_exec_time_logs":    CLEAR_EXEC_TIME_LOGS, # clear_logs()
    "clear_all":               CLEAR_ALL_LOGS        # clear_logs()
}
   
# -------- <parser_utils.py, my_parser.py> -------- #