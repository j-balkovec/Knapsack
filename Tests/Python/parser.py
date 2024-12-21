"""
@file_name: parser.py

@author: Jakob Balkovec
@date: December 2024

@description: This file parses the test_log log file and finds the ideal parameters ACO & SA algorithms.

@bugs: <NONE>
"""

from parser_utils import (parser_logger,
                          run_makefile_command,
                          dump_to_file,
                          clear_test_logs,
                          COLORS)

SA_PATHS: dict = {'LOG': r'/Users/jbalkovec/Desktop/Knapsack/Logs/SA_test.log',
                  'DUMP': r'/Users/jbalkovec/Desktop/Knapsack/Tests/Python/Dump/sa_dump.txt'}

ACO_PATHS: dict = {'LOG': r'/Users/jbalkovec/Desktop/Knapsack/Logs/ACO_test.log',
                    'DUMP': r'/Users/jbalkovec/Desktop/Knapsack/Tests/Python/Dump/aco_dump.txt'}

RUN_ACO = True
RUN_SA = False
def main():
  """
  This function runs the ACO algorithm and dumps the results to a file.
  """ 
  clear_test_logs()
  
  # ================================================================================================= #
  
  if RUN_SA:
    parser_logger.info("Starting SA algorithm.")
    run_makefile_command(["make", "run_sa"])
    success_sa: bool = dump_to_file(SA_PATHS)
    
    if success_sa:
      print(COLORS['green'] + "[SUCCESS] <check_log>: ../../SA_test.log." + COLORS['reset'] + "\n")
      parser_logger.info("SA algorithm ran successfully.")
      
    else:
      print(COLORS['red'] + "[ERROR] <check_log>: ../../SA_test.log." + COLORS['reset'])
      parser_logger.error("SA algorithm failed.")
      
    parser_logger.info("Finished SA algorithm.")
  
  # ================================================================================================= #
  
  if RUN_ACO:
    parser_logger.info("Starting ACO algorithm.")
    run_makefile_command(["make", "run_aco"])
    success_aco: bool = dump_to_file(SA_PATHS)
      
    if success_aco:
      print(COLORS['green'] + "[SUCCESS] <check_log>: ../../ACO_test.log." + COLORS['reset'] + "\n")
      parser_logger.info("ACO algorithm ran successfully.")
      
    else:
      print(COLORS['red'] + "[ERROR] <check_log>: ../../ACO_test.log." + COLORS['reset'])
      parser_logger.error("ACO algorithm failed.")
      
    dump_to_file(ACO_PATHS)
    parser_logger.info("Finished ACO algorithm.")

  # ================================================================================================= #
  
if __name__ == "__main__":
  main()