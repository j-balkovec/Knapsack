"""
@file_name: analysis.py

@author: Jakob Balkovec
@date: December 2024

@description: This file essentially finds the optimal parameters for the ACO and SA algorithm.

@bugs: <NONE>
"""
import sys
import os

sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), "../../Python")))

from my_parser import (get_entries_sa,
                       get_entries_aco)



