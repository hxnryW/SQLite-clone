#!/bin/bash

# Run your database binary
echo "insert 1 user1 email1@example.com" | ./db > output.txt
echo "insert 2 user2 email2@example.com" | ./db >> output.txt
echo "select" | ./db >> output.txt
echo ".exit" | ./db >> output.txt

# Check if the output contains expected results
if grep -q "(1, user1, email1@example.com)" output.txt &&
   grep -q "(2, user2, email2@example.com)" output.txt; then
    echo "✅ Test Passed"
else
    echo "❌ Test Failed"
    cat output.txt
fi

