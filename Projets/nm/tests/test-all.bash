#!/usr/bin/env bash

# Define color codes
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[0;33m'
NC='\033[0m' # No Color

mapfile -t executables < <(find ./tests/bin -type f)

mapfile -t subdir_executables < <(find ./tests/bin2 -type f)
executables+=("${subdir_executables[@]}")

mapfile -t subdir_executables < <(find ./tests/bin3 -type f)
executables+=("${subdir_executables[@]}")

executables+=("./ft_nm" "dsgbhsdg")

total_tests=0
total_success=0
total_fail=0

echo -e "\n${YELLOW}===================== TESTS =====================${NC}"

start_time=$(date +%s%N)
for executable in "${executables[@]}"; do
  nm_result=$(nm "$executable" 2>&1)
  ft_nm_result=$(./ft_nm "$executable" 2>&1)

  # Remove the prefix and compare the results
  nm_result_clean=$(echo "$nm_result" | sed '/^nm/d')
  ft_nm_result_clean=$(echo "$ft_nm_result" | sed '/^ft_nm/d')

  if diff <(echo "$nm_result_clean") <(echo "$ft_nm_result_clean") > /dev/null; then
    echo -e "${YELLOW}$executable${NC} => ${GREEN}OK${NC}"
    total_success=$((total_success + 1))
  else
    echo -e "${YELLOW}$executable${NC} => ${RED}KO${NC}"
    total_fail=$((total_fail + 1))
  fi
  total_tests=$((total_tests + 1))
done

end_time=$(date +%s%N)
duration=$((end_time - start_time))

# Convert duration to seconds and minutes
duration_sec=$((duration / 1000000000))
duration_min=$((duration_sec / 60))
duration_sec=$((duration_sec % 60))

echo -e "\n${YELLOW}===================== RESULTS =====================${NC}"
echo -e "Total duration: ${duration_min}m ${duration_sec}s"
echo -e "Total tests: ${total_tests}"
echo -e "Total success: ${GREEN}${total_success}${NC}"
echo -e "Total fail: ${RED}${total_fail}${NC}"