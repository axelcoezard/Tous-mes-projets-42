#!/usr/bin/env bash

# Define color codes
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[0;33m'
NC='\033[0m' # No Color

executable=$1

echo -e "\n${YELLOW}================= TEST: $executable =================${NC}"

start_time=$(date +%s%N)

nm_result=$(nm "$executable" 2>&1)
ft_nm_result=$(./ft_nm "$executable" 2>&1)

nm_result_clean=$(echo "$nm_result" | sed '/^nm/d')
ft_nm_result_clean=$(echo "$ft_nm_result" | sed '/^ft_nm/d')

if diff <(echo "$nm_result_clean") <(echo "$ft_nm_result_clean") > /dev/null; then
  echo -e "${YELLOW}$executable${NC} => ${GREEN}OK${NC}"
else
  echo -e "${YELLOW}$executable${NC} => ${RED}KO${NC}"
fi

end_time=$(date +%s%N)
duration=$((end_time - start_time))

# Convert duration to seconds and minutes
duration_sec=$((duration / 1000000000))
duration_min=$((duration_sec / 60))
duration_sec=$((duration_sec % 60))

echo -e "\n${YELLOW}===================== STATS =====================${NC}"
echo -e "Total duration: ${duration_min}m ${duration_sec}s"