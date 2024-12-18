"""
@file_name: input_generator.py

@author: Jakob Balkovec
@date: December 2024

@description: This file contains the input generator for the project. It will generate the data for the Knapsack project.

@bugs: <NONE>
"""
import random
import datetime
import os
import csv
import logging

from constants import (LOWER_BOUND_ITEMS,
                       UPPER_BOUND_ITEMS,
                       LOWER_BOUND_CAPACITY,
                       UPPER_BOUND_CAPACITY,
                       ITEMS,
                       CAPACITY,
                       SIZE_MAP,
                       CAPACITY_SIZE,
                       LOG_PATH,
                       BREAK,
                       MEGA_TAB,
                       DELETE_LOG)

def instantiate_logger() -> logging.Logger:
    """Creates and configures a logger for the script."""
    os.makedirs(os.path.dirname(LOG_PATH), exist_ok=True)

    logger = logging.getLogger(__name__)
    logger.setLevel(logging.INFO)
    formatter = logging.Formatter('%(asctime)s - %(name)s - %(levelname)s - %(message)s')

    file_handler = logging.FileHandler(LOG_PATH)
    file_handler.setFormatter(formatter)
    logger.addHandler(file_handler)
    return logger

def create_data_file_name(size, data_type):
    """Generates a data file name based on the specified size and type."""
    timestamp = datetime.datetime.now().strftime('%d_%m_%Y')
    return f"{data_type}_{size}_{timestamp}.csv" if data_type == ITEMS else f"{data_type}_{timestamp}.csv"

def create_items_data(size):
    """Creates a list of dictionaries representing items with random weights and values."""
    return [
        {"Weight": random.randint(LOWER_BOUND_ITEMS, UPPER_BOUND_ITEMS),
         "Value": random.randint(LOWER_BOUND_ITEMS, UPPER_BOUND_ITEMS)}
        for _ in range(SIZE_MAP[size])
    ]

def create_capacity_data(size=CAPACITY_SIZE):
    """Creates a list of dictionaries representing capacities with random values."""
    return [
        {"Capacity": random.randint(LOWER_BOUND_CAPACITY, UPPER_BOUND_CAPACITY)}
        for _ in range(size)
    ]

def write_to_csv(data, file_path, headers, logger):
    """Writes data to a CSV file."""
    os.makedirs(os.path.dirname(file_path), exist_ok=True)
    try:
        with open(file_path, mode='w', newline='') as file:
            writer = csv.DictWriter(file, fieldnames=headers)
            writer.writeheader()
            writer.writerows(data)
        logger.info(f"[SUCCESS]: Created {file_path}")
        return file_path
    except Exception as e:
        logger.error(f"[ERROR]: Failed to create {file_path}: {e}")
        return None

def create_data_file(size, data, data_type, logger):
    """Creates a CSV data file with the specified data and type."""
    headers = ["Weight", "Value"] if data_type == ITEMS else ["Capacity"]
    file_name = create_data_file_name(size, data_type)
    file_path = os.path.join('Data', data_type, file_name)
    return write_to_csv(data, file_path, headers, logger)

def delete_all_data_files(base_directory, logger):
    """Deletes all data files in the specified base directory."""
    for sub_dir in [ITEMS, CAPACITY]:
        directory = os.path.join(base_directory, sub_dir)
        if os.path.exists(directory):
            for file_name in os.listdir(directory):
                file_path = os.path.join(directory, file_name)
                if os.path.isfile(file_path):
                    os.remove(file_path)
                    logger.info(f"[SUCCESS]: Deleted {file_path}")
        else:
            raise FileNotFoundError(f"[ERROR]: Directory does not exist: {directory}")

def run_data_factory(logger):
    """Runs the data factory to create item and capacity data files for all sizes."""
    successful_files = []
    unsuccessful_files = []

    for size in SIZE_MAP.keys():
        items_data = create_items_data(size)
        result = create_data_file(size, items_data, ITEMS, logger)
        if result:
            successful_files.append(result)
        else:
            unsuccessful_files.append(f"items_{size}")

    capacity_data = create_capacity_data()
    result = create_data_file('all', capacity_data, CAPACITY, logger)
    if result:
        successful_files.append(result)
    else:
        unsuccessful_files.append("capacity")

    logger.info(BREAK + MEGA_TAB + "*** [Successfully created data files] ***")
    for file in successful_files:
        logger.info(f"        - {file}")

    logger.info(BREAK + MEGA_TAB + "*** [Unsuccessful file creations] ***")
    if unsuccessful_files:
        for file in unsuccessful_files:
            logger.info(f"        - {file}")
    else:
        logger.info("        - None\n")

def clear_log_file():
    """Clears the log file."""
    with open(LOG_PATH, 'w') as file:
        file.write('')
        
def main():
    """Main function to delete existing data files and run the data factory."""
    clear_log_file() if DELETE_LOG else None
    
    input_generator_logger = instantiate_logger()
    
    # Un-comment if you wish to delete all data files before running the data factory
    # try:
    #     delete_all_data_files('Data', input_generator_logger)
    # except FileNotFoundError as e:
    #     input_generator_logger.error(e)
    
    run_data_factory(input_generator_logger)

if __name__ == '__main__':
    main()
