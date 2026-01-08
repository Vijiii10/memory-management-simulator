#!/bin/bash

echo "Running allocator tests"
./memsim < tests/allocator_tests.txt

echo "Running buddy tests"
./memsim < tests/buddy_tests.txt

echo "Running cache tests"
./memsim < tests/cache_tests.txt

echo "Running VM tests"
./memsim < tests/vm_tests.txt
