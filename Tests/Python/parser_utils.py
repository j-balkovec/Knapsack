"""
@file_name: parser_utils.py

@author: Jakob Balkovec
@date: December 2024

@description: This file contains the "main" function for parsing the log file.

@bugs: <NONE>
"""
import re
import logging
import os
import sys
import subprocess
import select

# Logs parser output to a file
LOG_PATH = r'/Users/jbalkovec/Desktop/Knapsack/Logs/parser_log.log' 

# 'a' = append, 'w' = write
DUMP_TYPE = 'w'

# Colors for terminal output
COLORS: dict = {'red': '\033[91m',
                'green': '\033[92m',
                'yellow': '\033[93m',
                'blue': '\033[94m',
                'magenta': '\033[95m',
                'cyan': '\033[96m',
                'white': '\033[97m',
                'reset': '\033[0m'}   

class LogEntry:
  def __init__(self: object, 
         name: str, 
         parameters: str, 
         execution_time: int, 
         capacity: int, 
         solution: int, 
         items_size: int):
    """
    Initializes an object of the ParserUtils class.

    Args:
      name (str): The name of the object.
      parameters (str): The parameters of the object.
      execution_time (int): The execution time of the object.
      capacity (int): The capacity of the object.
      solution (int): The solution of the object.
      items_size (int): The size of the items.

    Returns:
      None
    """
    self.name = name
    self.parameters = parameters
    self.execution_time = execution_time
    self.capacity = capacity
    self.solution = solution
    self.items_size = items_size
  
  def __repr__(self):
    """
    Returns a string representation of the RunEntry object.

    The string representation includes the name, parameters, execution time,
    capacity, solution, and items size of the RunEntry object.

    Returns:
      str: A string representation of the RunEntry object.
    """
    return (
      f"RunEntry(\n"
      f"  <name>           = {self.name},\n"
      f"  <parameters>     = {self.parameters}\n"
      f"  <execution_time> = {self.execution_time}\n"
      f"  <capacity>       = {self.capacity}\n"
      f"  <solution>       = {self.solution}\n"
      f"  <items_size>     = {self.items_size}\n"
      f")"
    )
    
  def __str__(self):
    """
    Returns a string representation of the RunEntry object, used for casting.

    The string representation includes the name, parameters, execution time,
    capacity, solution, and items size of the RunEntry object.

    Returns:
      str: A string representation of the RunEntry object.
    """
    return (
      f"RunEntry(\n"
      f"  <name>           = {self.name},\n"
      f"  <parameters>     = {self.parameters}\n"
      f"  <execution_time> = {self.execution_time}\n"
      f"  <capacity>       = {self.capacity}\n"
      f"  <solution>       = {self.solution}\n"
      f"  <items_size>     = {self.items_size}\n"
      f")"
    )

def instantiate_logger() -> logging.Logger:
  """Creates and configures a logger for the script.

  Returns:
    logging.Logger: The configured logger object.
  """
  os.makedirs(os.path.dirname(LOG_PATH), exist_ok=True)

  logger = logging.getLogger(__name__)
  logger.setLevel(logging.INFO)
  formatter = logging.Formatter('%(asctime)s - %(name)s - %(levelname)s - %(message)s')

  file_handler = logging.FileHandler(LOG_PATH)
  file_handler.setFormatter(formatter)
  logger.addHandler(file_handler)
  return logger

# Logger
parser_logger = instantiate_logger()

def parse_log_file(file_path):
  """
  Parses a log file and extracts relevant information to create LogEntry objects.

  Args:
    file_path (str): The path to the log file.

  Returns:
    list: A list of LogEntry objects containing the parsed information from the log file.
  """
  parser_logger.info(f"Starting to parse log file: {file_path}")
  
  try:
    with open(file_path, 'r') as f:
      lines = f.readlines()[5:]  # skip the first 5 lines
      parser_logger.info(f"Successfully read log file. Skipped the first 5 lines. Total lines: {len(lines)}")
  except FileNotFoundError:
    parser_logger.error(f"File not found: {file_path}")
    return []
  except Exception as e:
    parser_logger.exception(f"An error occurred while reading the file: {file_path}")
    return []

  entries = []
  current_entry = {}
  
  for idx, line in enumerate(lines, start=6):  # adjust index due to skipped lines
    try:
      if "===" in line:
        if current_entry:  
          current_entry.setdefault('name', "Unknown")
          current_entry.setdefault('parameters', "No parameters")
          current_entry.setdefault('execution_time', 0)
          current_entry.setdefault('capacity', 0)
          current_entry.setdefault('solution', 0)
          current_entry.setdefault('items_size', 0)
          
          entry = LogEntry(**current_entry)
          entries.append(entry)
          parser_logger.info(f"Added LogEntry at line {idx}")
          current_entry = {}
      elif "[warning]" in line:  
        current_entry['parameters'] = line.strip().split("[warning] ")[1]
        parser_logger.debug(f"Found parameters at line {idx}: {current_entry['parameters']}")
      else:
        if match := re.search(r"\[name\]: <a> (.+)", line):
          current_entry['name'] = match.group(1)
          parser_logger.debug(f"Found name at line {idx}: {current_entry['name']}")
        elif match := re.search(r"\[execution_time\]: (\d+)", line):
          current_entry['execution_time'] = int(match.group(1))
          parser_logger.debug(f"Found execution_time at line {idx}: {current_entry['execution_time']}")
        elif match := re.search(r"\[capacity\]: (\d+)", line):
          current_entry['capacity'] = int(match.group(1))
          parser_logger.debug(f"Found capacity at line {idx}: {current_entry['capacity']}")
        elif match := re.search(r"\[solution\]: (\d+)", line):
          current_entry['solution'] = int(match.group(1))
          parser_logger.debug(f"Found solution at line {idx}: {current_entry['solution']}")
        elif match := re.search(r"\[items_size\]: \[(\d+)\]", line):
          current_entry['items_size'] = int(match.group(1))
          parser_logger.debug(f"Found items_size at line {idx}: {current_entry['items_size']}")
    except Exception as e:
      parser_logger.error(f"Error processing line {idx}: {line.strip()}")
      parser_logger.exception(e)
  
  # handle last entry if present
  if current_entry:
    current_entry.setdefault('name', "Unknown")
    current_entry.setdefault('parameters', "No parameters")
    current_entry.setdefault('execution_time', 0)
    current_entry.setdefault('capacity', 0)
    current_entry.setdefault('solution', 0)
    current_entry.setdefault('items_size', 0)
    
    entry = LogEntry(**current_entry)
    entries.append(entry)
    parser_logger.info(f"Added final LogEntry: {entry}")

  parser_logger.info(f"Finished parsing log file. Total entries: {len(entries)}")
  return entries

def clean_and_sort_entries(entries: list[LogEntry]) -> list[LogEntry]:
  """
  Removes faulty entries and entries with no parameters from the given list of LogEntry objects.

  Args:
    entries (list[LogEntry]): The list of LogEntry objects to be cleaned.

  Returns:
    list[LogEntry]: The cleaned list of LogEntry objects.
  """
  for entry in entries:
    if entry.name == "Unknown" or entry.name == "Dynamic Programming":
      parser_logger.warning(f"Faulty Entry: {entry}")
      entries.remove(entry)
    
    # idk why, but some objects don't hit the first if statement
    if entry.items_size == 0:
      parser_logger.warning(f"Faulty Entry: {entry}")
      entries.remove(entry)
      
    if entry.parameters == "No parameters":
      parser_logger.warning(f"Faulty Entry: {entry}")
      entries.remove(entry)
        
  return sorted(entries, key=lambda x: x.solution, reverse=True)

def run_makefile_command(commands: list):
  """
  Runs the specified commands in the directory containing C++ tests.

  Args:
    commands (list): A list of commands to be executed.

  Returns:
    None: This function does not return any value.

  Raises:
    Exception: If there is an error changing the directory or executing the commands.
  """
  cpp_tests_dir = os.path.join(os.path.dirname(__file__), "..", "C++")
  cpp_tests_dir = os.path.abspath(cpp_tests_dir)
  
  try:
    os.chdir(cpp_tests_dir)
    print(COLORS['green'] + f"Changed directory to {cpp_tests_dir}" + COLORS['reset'])
  except Exception as e:
    print(COLORS['red'] + f"Error changing directory: {e}" + COLORS['reset'])
    return

  try:
    process = subprocess.Popen(commands, 
                stdout=subprocess.PIPE, 
                stderr=subprocess.PIPE, 
                text=True,
                bufsize=1)
    
    # ======================================================= #
    print(COLORS['yellow'] + "\n<make output>:" + COLORS['reset'])
    for stdout_line in iter(process.stdout.readline, ''):
      print(stdout_line, end='')
    process.stdout.close()
    # ======================================================= #
      
    print(COLORS['yellow'] + "\n<make error>:" + COLORS['reset'])
    for stderr_line in iter(process.stderr.readline, ''):
      print(stderr_line, end='')
    process.stderr.close()

    return_code = process.wait()
    print(COLORS['magenta'] + f"\n<return code>: {return_code}" + COLORS['reset'] + "\n")
    
    if process.returncode != 0:
      print(COLORS['red'] + "<make command failed>" + COLORS['reset'])
    else:
      print(COLORS['green'] + "<make command successful>" + COLORS['reset'] + "\n")
  except Exception as e:
    print(COLORS['red'] + f"<error>: {e}" + COLORS['reset'])

def dump_to_file(paths: dict) -> bool:
    """
    Dump the cleaned and sorted entries from the log file to a dump file.

    Args:
        paths (dict): A dictionary containing the paths to the log file and the dump file.

    Returns:
        bool: True if the operation was successful, False if an error occurred.
    """
    try:
        entries = clean_and_sort_entries(parse_log_file(paths['LOG']))
        str_entries = "".join(str(entry) for entry in entries)
        
        with open(paths['DUMP'], DUMP_TYPE) as file:
            file.write(str_entries)
        
        return True

    except Exception as e:
        print(f"Error: {e}")
        return False
    
def clear_test_logs():
  """
  Clears the test logs.

  Returns:
    None
  """
  os.chdir(r'/Users/jbalkovec/Desktop/Knapsack/Python/')
  
  subprocess.run(["python", "clear_logs.py"], check=True)
  
  return None
  
