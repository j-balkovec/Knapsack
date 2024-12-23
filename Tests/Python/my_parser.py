"""
@file_name: parser.py

@author: Jakob Balkovec
@date: December 2024

@description: This file parses the test_log log file and finds the ideal parameters ACO & SA algorithms.

@bugs: <NONE>
"""
import os
import sys

sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), "../../Python")))

from Python.clear_logs import (clear_logs,
                               clear_log) 

from Python.constants import (MAIN_LOG_PATH,
                              EXECUTION_TIME_LOG_PATH,
                              MIN_EXECUTION_TIME_LOG_PATH,
                              INPUT_GENERATOR_LOG_PATH,
                              UTILITY_LOG_PATH,
                              PARSER_LOG_PATH,
                              SA_TEST_LOG_PATH,
                              ACO_TEST_LOG_PATH,
                              TEST_LOG_PATH,
                              CLEAR_TEST_LOGS,
                              CLEAR_EXEC_TIME_LOGS,
                              ACO_DUMP_PATH,
                              SA_DUMP_PATH,
                              CLEAR_ALL_LOGS,
                              PATHS_CONFIG,
                              CONFIG,
                              COLORS) 

from Tests.Python.parser_utils import (parser_logger,
                          run_makefile_command,
                          dump_to_file)

MAKE_AUTO = False

SA_PATHS: dict = {'LOG': r'/Users/jbalkovec/Desktop/Knapsack/Logs/SA_test.log',
                  'DUMP': r'/Users/jbalkovec/Desktop/Knapsack/Tests/Python/Dump/sa_dump.txt'}

ACO_PATHS: dict = {'LOG': r'/Users/jbalkovec/Desktop/Knapsack/Logs/ACO_test.log',
                    'DUMP': r'/Users/jbalkovec/Desktop/Knapsack/Tests/Python/Dump/aco_dump.txt'}

# ================================================================================================= #
# <run_both> -> set both to True
RUN_ACO = True
RUN_SA = True
# ================================================================================================= #

# ================================================================================================= #
# Define the global entries variables with getter and setter
_ENTRIES_SA: list = []
_ENTRIES_ACO: list = []

def set_entries_sa(entries: list) -> None:
    """
    Setter for the entries of the simulated annealing algorithm.

    Args:
      entries (list): A list of entries to set for SA.

    Returns:
      None
    """
    global _ENTRIES_SA
    _ENTRIES_SA = entries

def get_entries_sa() -> list:
    """
    Getter for the entries of the simulated annealing algorithm.

    Returns:
      list: The current entries for SA.
    """
    return _ENTRIES_SA

def set_entries_aco(entries: list) -> None:
    """
    Setter for the entries of the ant colony optimization algorithm.

    Args:
      entries (list): A list of entries to set for ACO.

    Returns:
      None
    """
    global _ENTRIES_ACO
    _ENTRIES_ACO = entries

def get_entries_aco() -> list:
    """
    Getter for the entries of the ant colony optimization algorithm.

    Returns:
      list: The current entries for ACO.
    """
    return _ENTRIES_ACO
# ================================================================================================= #

def analyze_sa():
    """
    Analyzes the SA (Simulated Annealing) algorithm.

    This function runs the SA algorithm by executing a makefile command and dumps the results to a file.
    It also logs the success or failure of the algorithm and prints corresponding messages.

    Returns:
        None
    """
    parser_logger.info("Starting SA algorithm.")
    run_makefile_command(["make", "run_sa"]) if MAKE_AUTO else None
    success_sa, entries_sa = dump_to_file(SA_PATHS)
    
    # set entries
    set_entries_sa(entries_sa)
    
    if success_sa:
        print(COLORS['green'] + "[SUCCESS] <check_log>: ../../SA_test.log." + COLORS['reset'] + "\n")
        parser_logger.info("SA algorithm ran successfully.")
    else:
        print(COLORS['red'] + "[ERROR] <check_log>: ../../parser_log.log." + COLORS['reset'])
        parser_logger.error("SA algorithm failed.")
        
    parser_logger.info("Finished SA algorithm.")


def analyze_aco():
    """
    Analyzes the Ant Colony Optimization (ACO) algorithm.

    This function runs the ACO algorithm by executing a makefile command and
    dumps the results to a file. It also logs the success or failure of the algorithm.

    Returns:
        None
    """
    parser_logger.info("Starting ACO algorithm.")
    run_makefile_command(["make", "run_aco"]) if MAKE_AUTO else None
    success_aco, entries_aco = dump_to_file(ACO_PATHS)
    
    # set entries
    set_entries_aco(entries_aco)
    
    if success_aco:
        print(COLORS['green'] + "[SUCCESS] <check_log>: ../../ACO_test.log." + COLORS['reset'] + "\n")
        parser_logger.info("ACO algorithm ran successfully.")
    else:
        print(COLORS['red'] + "[ERROR] <check_log>: ../../parser_log.log." + COLORS['reset'])
        parser_logger.error("ACO algorithm failed.")
        
    parser_logger.info("Finished ACO algorithm.")
    

def clear_selected_logs():
    """
    Clears logs based on the CONFIG and PATHS_CONFIG dictionaries.
    Uses clear_log() for individual log files and clear_logs() for lists of logs.
    """
    parser_logger.info(f"Clearing selected logs. In file {__file__}. Starting the log clearance process.")
    
    for key, should_clear in CONFIG.items():
        parser_logger.debug(f"Checking configuration for key '{key}' with value {should_clear}.")
        
        if should_clear:
            if key not in PATHS_CONFIG:
                error_msg = f"Key '{key}' does not exist in PATHS_CONFIG."
                parser_logger.error(error_msg)
                raise KeyError(error_msg)
            
            path = PATHS_CONFIG[key]
            parser_logger.info(f"Key '{key}' is marked for clearance. Associated path: {path}.")
            
            # clear_logs for specific keys with list of paths
            if key in ["clear_exec_time_logs", "clear_test_logs", "clear_all"]:
                if isinstance(path, list):
                    parser_logger.info(f"Clearing logs from multiple paths for key '{key}'. Paths: {path}")
                    clear_logs(path)
                else:
                    error_msg = f"Expected a list of paths for key '{key}', but got {type(path).__name__}."
                    parser_logger.error(error_msg)
                    raise ValueError(error_msg)
            else:
                # clear_log for single paths
                if isinstance(path, str):
                    parser_logger.info(f"Clearing log from single path for key '{key}'. Path: {path}")
                    clear_log(path)
                else:
                    error_msg = f"Expected a single path for key '{key}', but got {type(path).__name__}."
                    parser_logger.error(error_msg)
                    raise ValueError(error_msg)
        else:
            parser_logger.debug(f"Skipping log clearance for key '{key}' as it is not marked for clearing.")
    
    parser_logger.info("Selected logs clearance process completed.")


def main():
    """
    This function runs the ACO algorithm and dumps the results to a file.
    """ 
    # clear_selected_logs() if MAKE_AUTO else None
    
    if RUN_SA:
        analyze_sa()
    
    if RUN_ACO:
        analyze_aco()
        
    aco_entries = get_entries_aco()
    sa_entries = get_entries_sa()

    print(aco_entries) # Bug: empty list
    print(sa_entries)
  
if __name__ == "__main__":
    main()
