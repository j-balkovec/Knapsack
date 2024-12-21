"""
@file_name: clear_logs.py

@author: Jakob Balkovec
@date: December 2024

@description: This script cleans the log files.

@bugs: <NONE>
"""

from constants import (MAIN_LOG_PATH,
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
                       COLORS)           

def clear_log(log_file: str) -> None:
  """
  Clears the specified log file.

  Args:
    log_file (str): The log file to be cleared.

  Returns:
    None: This function does not return any value.
  """
  clear: bool = confirm_clear_logs()
  if clear == True:
    with open(log_file, 'w') as f:
      f.write("")
    print(f"\n<log cleared: {log_file}>\n")
  
  else:
    print(f"\n<log not cleared: {log_file}>\n")
    
  
    
def clear_logs(log_files: list) -> None:
  """
  Clears the specified log files.

  Args:
    log_files (list): A list of log files to be cleared.

  Returns:
    None: This function does not return any value.
  """
  for log_file in log_files:
    clear_log(log_file)

def confirm_clear_logs() -> bool:
    confirmation = input(COLORS['yellow'] + " <are you sure you want to clear the logs? (y/n)> : " + COLORS['reset']).strip().lower()
    
    if confirmation in ['y', 'yes']:
        print(COLORS['green'] + "<clearing>" + COLORS['reset'])
        return True
    else:
        print(COLORS['red'] + "<aborting>" + COLORS['reset']) 
        return False 
    
# Run only under extreme caution. This will clear certain log files.

# clear_log(MAIN_LOG_PATH)
# clear_log(EXECUTION_TIME_LOG_PATH)
# clear_log(MIN_EXECUTION_TIME_LOG_PATH)
# clear_log(INPUT_GENERATOR_LOG_PATH)
# clear_log(UTILITY_LOG_PATH)
# clear_log(PARSER_LOG_PATH)
# clear_log(SA_TEST_LOG_PATH)
# clear_log(ACO_TEST_LOG_PATH)
# clear_log(TEST_LOG_PATH)

clear_logs(CLEAR_TEST_LOGS)
# clear_logs(CLEAR_EXEC_TIME_LOGS)
