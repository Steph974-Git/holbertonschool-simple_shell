#!/bin/bash

# Test basic exit (should return 0)
echo -e "\n--- Test 1: Basic exit ---"
echo "exit" > temp_script.sh
./hsh < temp_script.sh
echo "Return code: $?"

# Test exit with numeric argument (should return 98)
echo -e "\n--- Test 2: Exit with code 98 ---"
echo "exit 98" > temp_script.sh
./hsh < temp_script.sh
echo "Return code: $?"

# Test exit with invalid argument (should return 2)
echo -e "\n--- Test 3: Exit with invalid argument ---"
echo "exit abc" > temp_script.sh
./hsh < temp_script.sh
echo "Return code: $?"

# Test exit with too many arguments (test if you handle this case)
echo -e "\n--- Test 4: Exit with too many arguments ---"
echo "exit 98 extra" > temp_script.sh
./hsh < temp_script.sh
echo "Return code: $?"

# Test exit with negative number
echo -e "\n--- Test 5: Exit with negative number ---"
echo "exit -1" > temp_script.sh
./hsh < temp_script.sh
echo "Return code: $?"

# Test exit with large number (>255)
echo -e "\n--- Test 6: Exit with large number ---"
echo "exit 256" > temp_script.sh
./hsh < temp_script.sh
echo "Return code: $?"

# Clean up
rm temp_script.sh

