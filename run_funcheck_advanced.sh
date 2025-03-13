#!/bin/bash

# Colors for output
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[0;33m'
BLUE='\033[0;34m'
CYAN='\033[0;36m'
MAGENTA='\033[0;35m'
BOLD='\033[1m'
UNDERLINE='\033[4m'
NC='\033[0m' # No Color

# Check if funcheck is installed
if ! command -v funcheck &> /dev/null; then
	echo -e "${RED}Error: funcheck is not installed or not in PATH${NC}"
	exit 1
fi

# Check if cub3D executable exists
if [ ! -f "./cub3D" ]; then
	echo -e "${RED}Error: cub3D executable not found in current directory${NC}"
	exit 1
fi

# Function to show usage
show_usage() {
	echo -e "${YELLOW}Usage:${NC}"
	echo -e "  $0 [category]"
	echo -e "\n${YELLOW}Available categories:${NC}"
	echo -e "  all      - Run all tests (default)"
	echo -e "  texture  - Run only texture tests"
	echo -e "  color    - Run only color tests"
	echo -e "  basic    - Run only basic tests"
	echo -e "  good     - Run only good tests"
	echo -e "  extension - Run only extension tests"
	echo -e "  final    - Run only final tests"
	echo -e "  root     - Run only root tests"
	exit 1
}

# Parse command line arguments
CATEGORY="all"
if [ $# -gt 0 ]; then
	CATEGORY="$1"
fi

# Validate category
if [ "$CATEGORY" != "all" ] && [ "$CATEGORY" != "texture" ] && [ "$CATEGORY" != "color" ] && \
   [ "$CATEGORY" != "basic" ] && [ "$CATEGORY" != "good" ] && [ "$CATEGORY" != "extension" ] && \
   [ "$CATEGORY" != "final" ] && [ "$CATEGORY" != "root" ]; then
	echo -e "${RED}Error: Invalid category '$CATEGORY'${NC}"
	show_usage
fi

# Create results directory
RESULTS_DIR="funcheck_results"
mkdir -p "$RESULTS_DIR"

# Create or clear the summary file
SUMMARY_FILE="$RESULTS_DIR/summary.txt"
echo "Funcheck Test Summary" > "$SUMMARY_FILE"
echo "===================" >> "$SUMMARY_FILE"
echo "Category: $CATEGORY" >> "$SUMMARY_FILE"
echo "" >> "$SUMMARY_FILE"

# Initialize counters
TOTAL=0
PASSED=0
FAILED=0

# Category counters
declare -A CATEGORY_TOTAL
declare -A CATEGORY_PASSED
declare -A CATEGORY_FAILED

# Function to get category from map path
get_category() {
	local map_file="$1"
	
	if [[ "$map_file" == maps/good/* ]]; then
		echo "good"
	elif [[ "$map_file" == maps/basic/* ]]; then
		echo "basic"
	elif [[ "$map_file" == maps/color/* ]]; then
		echo "color"
	elif [[ "$map_file" == maps/texture/* ]]; then
		echo "texture"
	elif [[ "$map_file" == maps/extention/* ]]; then
		echo "extension"
	elif [[ "$map_file" == maps/final/* ]]; then
		echo "final"
	else
		echo "root"
	fi
}

# Function to extract error message
extract_error() {
	local log_file="$1"
	local error_msg=$(grep -A 1 "TTY" "$log_file" | tail -n 1 | sed 's/^[^:]*: //')
	
	if [ -z "$error_msg" ]; then
		echo "Unknown error"
	else
		echo "$error_msg"
	fi
}

# Function to check if file is expected to pass or fail
check_file_type_result() {
	local map_file="$1"
	local output_file="$2"
	local basename=$(basename "$map_file")
	local result=0
	
	# Check for specific file types
	if [[ "$basename" == r_* ]]; then
		# r_ files should contain "we are good to go"
		if grep -q "we are good to go" "$output_file"; then
			echo -e "\n${GREEN}${BOLD}✓ PASSED: 'we are good to go' found as expected${NC}"
			result=0
		else
			echo -e "\n${RED}${BOLD}✗ FAILED: 'we are good to go' not found${NC}"
			result=1
		fi
	elif [[ "$basename" == w_* ]]; then
		# w_ files should NOT contain "we are good to go"
		if ! grep -q "we are good to go" "$output_file"; then
			echo -e "\n${GREEN}${BOLD}✓ PASSED: 'we are good to go' not found as expected${NC}"
			result=0
		else
			echo -e "\n${RED}${BOLD}✗ FAILED: 'we are good to go' found but shouldn't be${NC}"
			result=1
		fi
	else
		# Other files - no specific check
		echo -e "\n${YELLOW}${BOLD}? UNKNOWN FILE TYPE: No specific check applied${NC}"
		result=0
	fi
	
	return $result
}

# Function to run funcheck on a single map
run_test() {
	local map_file="$1"
	local category=$(get_category "$map_file")
	
	# Skip if we're not running all categories and this isn't the target category
	if [ "$CATEGORY" != "all" ] && [ "$CATEGORY" != "$category" ]; then
		return
	fi
	
	local relative_path="${map_file#maps/}"
	local output_file="$RESULTS_DIR/${relative_path//\//_}.log"
	local basename=$(basename "$map_file")
	
	# Create a more prominent separator
	echo -e "\n\n${YELLOW}=================================================================${NC}"
	echo -e "${YELLOW}=                                                               =${NC}"
	echo -e "${YELLOW}=       ${BOLD}${UNDERLINE}${MAGENTA}Testing: ${map_file}${NC}${YELLOW}       =${NC}"
	echo -e "${YELLOW}=                                                               =${NC}"
	echo -e "${YELLOW}=================================================================${NC}\n"
	
	# Run funcheck and capture output while also displaying it
	funcheck -a ./cub3D "$map_file" | tee "$output_file"
	local exit_code=${PIPESTATUS[0]}
	
	# Initialize category counters if not already done
	if [ -z "${CATEGORY_TOTAL[$category]}" ]; then
		CATEGORY_TOTAL[$category]=0
		CATEGORY_PASSED[$category]=0
		CATEGORY_FAILED[$category]=0
	fi
	
	# Check file type specific results
	check_file_type_result "$map_file" "$output_file"
	local test_result=$?
	
	# Update statistics
	if [ $test_result -eq 0 ]; then
		echo "PASSED: $map_file" >> "$SUMMARY_FILE"
		((PASSED++))
		((CATEGORY_PASSED[$category]++))
	else
		local error_msg=$(extract_error "$output_file")
		echo "FAILED: $map_file - $error_msg" >> "$SUMMARY_FILE"
		((FAILED++))
		((CATEGORY_FAILED[$category]++))
	fi
	
	((TOTAL++))
	((CATEGORY_TOTAL[$category]++))
	
	# Add a closing separator
	echo -e "\n${YELLOW}=================================================================${NC}"
}

# Find all .cub files and run tests
echo -e "${YELLOW}${BOLD}Starting funcheck tests for category: ${CATEGORY}${NC}"
echo ""

# Process files in the main maps directory
for map_file in maps/*.cub; do
	if [ -f "$map_file" ]; then
		run_test "$map_file"
	fi
done

# Process files in subdirectories
for dir in maps/*/; do
	if [ -d "$dir" ]; then
		dir_name=$(basename "$dir")
		echo -e "\n\n${YELLOW}${BOLD}${UNDERLINE}Testing maps in ${dir_name}/${NC}\n"
		
		for map_file in "$dir"*.cub; do
			if [ -f "$map_file" ]; then
				run_test "$map_file"
			fi
		done
	fi
done

# Print summary
echo -e "\n\n${YELLOW}${BOLD}${UNDERLINE}Test Summary for ${CATEGORY}:${NC}"
echo -e "${BLUE}Total tests: ${TOTAL}${NC}"
echo -e "${GREEN}Passed: ${PASSED}${NC}"
echo -e "${RED}Failed: ${FAILED}${NC}"

# Add summary to summary file
echo "" >> "$SUMMARY_FILE"
echo "Summary:" >> "$SUMMARY_FILE"
echo "Total tests: $TOTAL" >> "$SUMMARY_FILE"
echo "Passed: $PASSED" >> "$SUMMARY_FILE"
echo "Failed: $FAILED" >> "$SUMMARY_FILE"

# Print category summary
echo -e "\n${YELLOW}${BOLD}${UNDERLINE}Category Summary:${NC}"
echo "" >> "$SUMMARY_FILE"
echo "Category Summary:" >> "$SUMMARY_FILE"

for category in "${!CATEGORY_TOTAL[@]}"; do
	total=${CATEGORY_TOTAL[$category]}
	passed=${CATEGORY_PASSED[$category]}
	failed=${CATEGORY_FAILED[$category]}
	
	if [ $total -eq 0 ]; then
		continue
	fi
	
	pass_percent=$((passed * 100 / total))
	
	echo -e "${CYAN}${BOLD}${category}:${NC}"
	echo -e "  ${BLUE}Total: ${total}${NC}"
	echo -e "  ${GREEN}Passed: ${passed} (${pass_percent}%)${NC}"
	echo -e "  ${RED}Failed: ${failed}${NC}"
	
	echo "${category}:" >> "$SUMMARY_FILE"
	echo "  Total: $total" >> "$SUMMARY_FILE"
	echo "  Passed: $passed ($pass_percent%)" >> "$SUMMARY_FILE"
	echo "  Failed: $failed" >> "$SUMMARY_FILE"
done

# Create a detailed HTML report
HTML_REPORT="$RESULTS_DIR/report.html"

cat > "$HTML_REPORT" << EOF
<!DOCTYPE html>
<html>
<head>
	<title>Funcheck Test Results - ${CATEGORY}</title>
	<style>
		body { font-family: Arial, sans-serif; margin: 20px; }
		h1, h2 { color: #333; }
		.summary { margin-bottom: 20px; }
		.category { margin-bottom: 30px; }
		table { border-collapse: collapse; width: 100%; }
		th, td { border: 1px solid #ddd; padding: 8px; text-align: left; }
		th { background-color: #f2f2f2; }
		tr:nth-child(even) { background-color: #f9f9f9; }
		.passed { color: green; }
		.failed { color: red; }
		.filter-buttons { margin-bottom: 15px; }
		button { margin-right: 5px; padding: 5px 10px; cursor: pointer; }
		.active { background-color: #4CAF50; color: white; }
	</style>
	<script>
		function filterTests(status) {
			var rows = document.querySelectorAll('table tr');
			for (var i = 1; i < rows.length; i++) {
				var row = rows[i];
				if (status === 'all' || row.classList.contains(status)) {
					row.style.display = '';
				} else {
					row.style.display = 'none';
				}
			}
			
			// Update active button
			var buttons = document.querySelectorAll('.filter-buttons button');
			for (var i = 0; i < buttons.length; i++) {
				buttons[i].classList.remove('active');
				if (buttons[i].getAttribute('data-filter') === status) {
					buttons[i].classList.add('active');
				}
			}
		}
	</script>
</head>
<body>
	<h1>Funcheck Test Results - ${CATEGORY}</h1>
	
	<div class="summary">
		<h2>Summary</h2>
		<p>Total tests: $TOTAL</p>
		<p>Passed: $PASSED</p>
		<p>Failed: $FAILED</p>
	</div>
	
	<div class="category-summary">
		<h2>Category Summary</h2>
EOF

# Add category summaries to HTML
for category in "${!CATEGORY_TOTAL[@]}"; do
	total=${CATEGORY_TOTAL[$category]}
	passed=${CATEGORY_PASSED[$category]}
	failed=${CATEGORY_FAILED[$category]}
	
	if [ $total -eq 0 ]; then
		continue
	fi
	
	pass_percent=$((passed * 100 / total))
	
	cat >> "$HTML_REPORT" << EOF
		<div class="category">
			<h3>$category</h3>
			<p>Total: $total</p>
			<p>Passed: $passed ($pass_percent%)</p>
			<p>Failed: $failed</p>
		</div>
EOF
done

# Start detailed results table
cat >> "$HTML_REPORT" << EOF
	</div>
	
	<div class="detailed-results">
		<h2>Detailed Results</h2>
		
		<div class="filter-buttons">
			<button data-filter="all" class="active" onclick="filterTests('all')">All</button>
			<button data-filter="passed" onclick="filterTests('passed')">Passed</button>
			<button data-filter="failed" onclick="filterTests('failed')">Failed</button>
		</div>
		
		<table>
			<tr>
				<th>Map</th>
				<th>Category</th>
				<th>Status</th>
				<th>File Type</th>
				<th>View Log</th>
			</tr>
EOF

# Add each test result to the HTML table
for map_file in $(find maps -name "*.cub" | sort); do
	if [ -f "$map_file" ]; then
		category=$(get_category "$map_file")
		
		# Skip if we're not running all categories and this isn't the target category
		if [ "$CATEGORY" != "all" ] && [ "$CATEGORY" != "$category" ]; then
			continue
		fi
		
		relative_path="${map_file#maps/}"
		output_file="$RESULTS_DIR/${relative_path//\//_}.log"
		log_file_name="${relative_path//\//_}.log"
		basename=$(basename "$map_file")
		
		if [ -f "$output_file" ]; then
			# Check file type specific results
			if [[ "$basename" == r_* ]]; then
				file_type="r_type"
				if grep -q "we are good to go" "$output_file"; then
					status="PASSED"
					status_class="passed"
					error_msg=""
				else
					status="FAILED"
					status_class="failed"
					error_msg="'we are good to go' not found"
				fi
			elif [[ "$basename" == w_* ]]; then
				file_type="w_type"
				if ! grep -q "we are good to go" "$output_file"; then
					status="PASSED"
					status_class="passed"
					error_msg=""
				else
					status="FAILED"
					status_class="failed"
					error_msg="'we are good to go' found but shouldn't be"
				fi
			else
				file_type="other"
				status="INFO"
				status_class="passed"
				error_msg="No specific check"
			fi
			
			cat >> "$HTML_REPORT" << EOF
			<tr class="$status_class">
				<td>$map_file</td>
				<td>$category</td>
				<td class="$status_class">$status</td>
				<td>$file_type</td>
				<td><a href="$log_file_name" target="_blank">View Log</a></td>
			</tr>
EOF
		fi
	fi
done

# Close HTML file
cat >> "$HTML_REPORT" << EOF
		</table>
	</div>
</body>
</html>
EOF

echo ""
echo -e "${YELLOW}Detailed results saved in ${RESULTS_DIR}/${NC}"
echo -e "${MAGENTA}HTML report generated at ${HTML_REPORT}${NC}" 