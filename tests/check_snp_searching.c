#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <check.h>
#include "check_snp_searching.h"
#include "helper_methods.h"

#include "../snp_searching.h"


START_TEST (check_find_starting_index_windows)
{
	int coords_empty[0] = {};
	int coords_one[1] = {1};
	int coords_odd[3] = {1,3,5};
	int coords_even[4] = {1,3,5,7};
	
	fail_unless( find_starting_index(0, coords_empty, 0, 0) == 0);
  fail_unless( find_starting_index(0, coords_one, 0, 1) == 0);
	fail_unless( find_starting_index(1, coords_one, 0, 1) == 0);
	
  fail_unless( find_starting_index(1, coords_odd, 0, 3) == 0);
  fail_unless( find_starting_index(3, coords_odd, 0, 3) == 1);
  fail_unless( find_starting_index(5, coords_odd, 0, 3) == 2);
  
  fail_unless( find_starting_index(0, coords_odd, 0, 3) == 0);
  fail_unless( find_starting_index(2, coords_odd, 0, 3) == 0);
  fail_unless( find_starting_index(4, coords_odd, 0, 3) == 1);
  
  fail_unless( find_starting_index(1, coords_even, 0, 4) == 0);
  fail_unless( find_starting_index(3, coords_even, 0, 4) == 1);
  fail_unless( find_starting_index(5, coords_even, 0, 4) == 2);
  fail_unless( find_starting_index(7, coords_even, 0, 4) == 3);
  fail_unless( find_starting_index(9, coords_even, 0, 4) == 3);
  
  fail_unless( find_starting_index(0, coords_even, 0, 4) == 0);
  fail_unless( find_starting_index(2, coords_even, 0, 4) == 0);
  fail_unless( find_starting_index(4, coords_even, 0, 4) == 1);
  fail_unless( find_starting_index(6, coords_even, 0, 4) == 2);
  fail_unless( find_starting_index(8, coords_even, 0, 4) == 3);
	
}
END_TEST

START_TEST (check_advance_window_start_to_next_snp)
{
  int coords_empty[0] = {};
  int coords_one[1]   = {1};
  int coords_odd[3]   = {1,3,5};
  int coords_even[4]  = {1,3,5,7};
	char *child_sequence_without_gaps = "ACGT";
	char *child_sequence_with_gaps = "-AG-";
	
	// Without gaps
	fail_unless( advance_window_start_to_next_snp(0, coords_empty,child_sequence_without_gaps,  0) == 0);
  fail_unless( advance_window_start_to_next_snp(0, coords_one,  child_sequence_without_gaps,  1) == 1);
	fail_unless( advance_window_start_to_next_snp(1, coords_one,  child_sequence_without_gaps,  1) == 1);
  fail_unless( advance_window_start_to_next_snp(1, coords_odd,  child_sequence_without_gaps,  3) == 1);
  fail_unless( advance_window_start_to_next_snp(3, coords_odd,  child_sequence_without_gaps,  3) == 3);
  fail_unless( advance_window_start_to_next_snp(5, coords_odd,  child_sequence_without_gaps,  3) == 5);
  fail_unless( advance_window_start_to_next_snp(0, coords_odd,  child_sequence_without_gaps,  3) == 1);
  fail_unless( advance_window_start_to_next_snp(2, coords_odd,  child_sequence_without_gaps,  3) == 3);
  fail_unless( advance_window_start_to_next_snp(4, coords_odd,  child_sequence_without_gaps,  3) == 5);
  fail_unless( advance_window_start_to_next_snp(1, coords_even, child_sequence_without_gaps,  4) == 1);
  fail_unless( advance_window_start_to_next_snp(3, coords_even, child_sequence_without_gaps,  4) == 3);
  fail_unless( advance_window_start_to_next_snp(5, coords_even, child_sequence_without_gaps,  4) == 5);
  fail_unless( advance_window_start_to_next_snp(7, coords_even, child_sequence_without_gaps,  4) == 7);
  fail_unless( advance_window_start_to_next_snp(9, coords_even, child_sequence_without_gaps,  4) == 9);
  fail_unless( advance_window_start_to_next_snp(0, coords_even, child_sequence_without_gaps,  4) == 1);
  fail_unless( advance_window_start_to_next_snp(2, coords_even, child_sequence_without_gaps,  4) == 3);
  fail_unless( advance_window_start_to_next_snp(4, coords_even, child_sequence_without_gaps,  4) == 5);
  fail_unless( advance_window_start_to_next_snp(6, coords_even, child_sequence_without_gaps,  4) == 7);
  fail_unless( advance_window_start_to_next_snp(8, coords_even, child_sequence_without_gaps,  4) == 8);

  // With gaps
	fail_unless( advance_window_start_to_next_snp(0, coords_empty,child_sequence_with_gaps,  0) == 0);
  fail_unless( advance_window_start_to_next_snp(0, coords_one,  child_sequence_with_gaps,  1) == 0);
	fail_unless( advance_window_start_to_next_snp(1, coords_one,  child_sequence_with_gaps,  1) == 1);
  fail_unless( advance_window_start_to_next_snp(1, coords_odd,  child_sequence_with_gaps,  3) == 3);
  fail_unless( advance_window_start_to_next_snp(3, coords_odd,  child_sequence_with_gaps,  3) == 3);
  fail_unless( advance_window_start_to_next_snp(5, coords_odd,  child_sequence_with_gaps,  3) == 5);
  fail_unless( advance_window_start_to_next_snp(0, coords_odd,  child_sequence_with_gaps,  3) == 3);
  fail_unless( advance_window_start_to_next_snp(2, coords_odd,  child_sequence_with_gaps,  3) == 3);
  fail_unless( advance_window_start_to_next_snp(4, coords_odd,  child_sequence_with_gaps,  3) == 5);
  fail_unless( advance_window_start_to_next_snp(1, coords_even, child_sequence_with_gaps,  4) == 3);
  fail_unless( advance_window_start_to_next_snp(3, coords_even, child_sequence_with_gaps,  4) == 3);
  fail_unless( advance_window_start_to_next_snp(5, coords_even, child_sequence_with_gaps,  4) == 5);
  fail_unless( advance_window_start_to_next_snp(7, coords_even, child_sequence_with_gaps,  4) == 7);
  fail_unless( advance_window_start_to_next_snp(9, coords_even, child_sequence_with_gaps,  4) == 9);
  fail_unless( advance_window_start_to_next_snp(0, coords_even, child_sequence_with_gaps,  4) == 3);
  fail_unless( advance_window_start_to_next_snp(2, coords_even, child_sequence_with_gaps,  4) == 3);
  fail_unless( advance_window_start_to_next_snp(4, coords_even, child_sequence_with_gaps,  4) == 5);
  fail_unless( advance_window_start_to_next_snp(6, coords_even, child_sequence_with_gaps,  4) == 6);
  fail_unless( advance_window_start_to_next_snp(8, coords_even, child_sequence_with_gaps,  4) == 8);
}
END_TEST

START_TEST (check_rewind_window_end_to_last_snp)
{
  int coords_empty[0] = {};
  int coords_one[1]   = {1};
  int coords_odd[3]   = {1,3,5};
  int coords_even[4]  = {1,3,5,7};
	char *child_sequence_without_gaps = "ACGT";
	char *child_sequence_with_gaps = "-AG-";
	
	// Without gaps
	fail_unless( rewind_window_end_to_last_snp(0, coords_empty,child_sequence_without_gaps,  0) == 0);
  fail_unless( rewind_window_end_to_last_snp(0, coords_one,  child_sequence_without_gaps,  1) == 0);
	fail_unless( rewind_window_end_to_last_snp(1, coords_one,  child_sequence_without_gaps,  1) == 1);
  fail_unless( rewind_window_end_to_last_snp(1, coords_odd,  child_sequence_without_gaps,  3) == 1);
  fail_unless( rewind_window_end_to_last_snp(3, coords_odd,  child_sequence_without_gaps,  3) == 3);
  fail_unless( rewind_window_end_to_last_snp(5, coords_odd,  child_sequence_without_gaps,  3) == 5);
  fail_unless( rewind_window_end_to_last_snp(0, coords_odd,  child_sequence_without_gaps,  3) == 0);
  fail_unless( rewind_window_end_to_last_snp(2, coords_odd,  child_sequence_without_gaps,  3) == 1);
  fail_unless( rewind_window_end_to_last_snp(4, coords_odd,  child_sequence_without_gaps,  3) == 3);
  fail_unless( rewind_window_end_to_last_snp(1, coords_even, child_sequence_without_gaps,  4) == 1);
  fail_unless( rewind_window_end_to_last_snp(3, coords_even, child_sequence_without_gaps,  4) == 3);
  fail_unless( rewind_window_end_to_last_snp(5, coords_even, child_sequence_without_gaps,  4) == 5);
  fail_unless( rewind_window_end_to_last_snp(7, coords_even, child_sequence_without_gaps,  4) == 7);
  fail_unless( rewind_window_end_to_last_snp(9, coords_even, child_sequence_without_gaps,  4) == 7);
  fail_unless( rewind_window_end_to_last_snp(0, coords_even, child_sequence_without_gaps,  4) == 0);
  fail_unless( rewind_window_end_to_last_snp(2, coords_even, child_sequence_without_gaps,  4) == 1);
  fail_unless( rewind_window_end_to_last_snp(4, coords_even, child_sequence_without_gaps,  4) == 3);
  fail_unless( rewind_window_end_to_last_snp(6, coords_even, child_sequence_without_gaps,  4) == 5);
  fail_unless( rewind_window_end_to_last_snp(8, coords_even, child_sequence_without_gaps,  4) == 7);


	fail_unless( rewind_window_end_to_last_snp(0, coords_empty,child_sequence_with_gaps,  0) == 0);
  fail_unless( rewind_window_end_to_last_snp(0, coords_one,  child_sequence_with_gaps,  1) == 0);
	fail_unless( rewind_window_end_to_last_snp(1, coords_one,  child_sequence_with_gaps,  1) == 1);
  fail_unless( rewind_window_end_to_last_snp(1, coords_odd,  child_sequence_with_gaps,  3) == 1);
  fail_unless( rewind_window_end_to_last_snp(3, coords_odd,  child_sequence_with_gaps,  3) == 3);
  fail_unless( rewind_window_end_to_last_snp(5, coords_odd,  child_sequence_with_gaps,  3) == 5);
  fail_unless( rewind_window_end_to_last_snp(0, coords_odd,  child_sequence_with_gaps,  3) == 0);
  fail_unless( rewind_window_end_to_last_snp(2, coords_odd,  child_sequence_with_gaps,  3) == 2);
  fail_unless( rewind_window_end_to_last_snp(4, coords_odd,  child_sequence_with_gaps,  3) == 3);
  fail_unless( rewind_window_end_to_last_snp(1, coords_even, child_sequence_with_gaps,  4) == 1);
  fail_unless( rewind_window_end_to_last_snp(3, coords_even, child_sequence_with_gaps,  4) == 3);
  fail_unless( rewind_window_end_to_last_snp(5, coords_even, child_sequence_with_gaps,  4) == 5);
  fail_unless( rewind_window_end_to_last_snp(7, coords_even, child_sequence_with_gaps,  4) == 5);
  fail_unless( rewind_window_end_to_last_snp(9, coords_even, child_sequence_with_gaps,  4) == 5);
  fail_unless( rewind_window_end_to_last_snp(0, coords_even, child_sequence_with_gaps,  4) == 0);
  fail_unless( rewind_window_end_to_last_snp(2, coords_even, child_sequence_with_gaps,  4) == 2);
  fail_unless( rewind_window_end_to_last_snp(4, coords_even, child_sequence_with_gaps,  4) == 3);
  fail_unless( rewind_window_end_to_last_snp(6, coords_even, child_sequence_with_gaps,  4) == 5);
  fail_unless( rewind_window_end_to_last_snp(8, coords_even, child_sequence_with_gaps,  4) == 5);
}
END_TEST

START_TEST (check_get_window_end_coordinates_excluding_gaps)
{
  int coords_empty[0] = {};
  int coords_one[1]   = {1};
  int coords_odd[3]   = {1,3,5};
  int coords_even[8]  = {1,3,5,7,11,13,17,19};
	char *child_sequence_without_gaps = "ACGTACGT";
	char *child_sequence_with_gaps = "-AC-GT-A";
	
	//int get_window_end_coordinates_excluding_gaps(1, 3, coords_even, char * child_sequence, int number_of_snps)

	fail_unless( get_window_end_coordinates_excluding_gaps(0, 3, coords_empty,child_sequence_without_gaps,  0) == 3);
  fail_unless( get_window_end_coordinates_excluding_gaps(0, 3, coords_one,  child_sequence_without_gaps,  1) == 3);
	fail_unless( get_window_end_coordinates_excluding_gaps(1, 3, coords_one,  child_sequence_without_gaps,  1) == 4);
  fail_unless( get_window_end_coordinates_excluding_gaps(1, 3, coords_odd,  child_sequence_without_gaps,  3) == 4);
  fail_unless( get_window_end_coordinates_excluding_gaps(3, 3, coords_odd,  child_sequence_without_gaps,  3) == 6);
  fail_unless( get_window_end_coordinates_excluding_gaps(5, 3, coords_odd,  child_sequence_without_gaps,  3) == 8);
  fail_unless( get_window_end_coordinates_excluding_gaps(0, 3, coords_odd,  child_sequence_without_gaps,  3) == 3);
  fail_unless( get_window_end_coordinates_excluding_gaps(2, 3, coords_odd,  child_sequence_without_gaps,  3) == 5);
  fail_unless( get_window_end_coordinates_excluding_gaps(4, 3, coords_odd,  child_sequence_without_gaps,  3) == 7);
  fail_unless( get_window_end_coordinates_excluding_gaps(1, 3, coords_even, child_sequence_without_gaps,  8) == 4);
  fail_unless( get_window_end_coordinates_excluding_gaps(3, 3, coords_even, child_sequence_without_gaps,  8) == 6);
  fail_unless( get_window_end_coordinates_excluding_gaps(5, 3, coords_even, child_sequence_without_gaps,  8) == 8);
  fail_unless( get_window_end_coordinates_excluding_gaps(7, 3, coords_even, child_sequence_without_gaps,  8) == 10);
  fail_unless( get_window_end_coordinates_excluding_gaps(9, 3, coords_even, child_sequence_without_gaps,  8) == 12);
  fail_unless( get_window_end_coordinates_excluding_gaps(0, 3, coords_even, child_sequence_without_gaps,  8) == 3);
  fail_unless( get_window_end_coordinates_excluding_gaps(2, 3, coords_even, child_sequence_without_gaps,  8) == 5);
  fail_unless( get_window_end_coordinates_excluding_gaps(4, 3, coords_even, child_sequence_without_gaps,  8) == 7);
  fail_unless( get_window_end_coordinates_excluding_gaps(6, 3, coords_even, child_sequence_without_gaps,  8) == 9);
  fail_unless( get_window_end_coordinates_excluding_gaps(8, 3, coords_even, child_sequence_without_gaps,  8) == 11);
           
	fail_unless( get_window_end_coordinates_excluding_gaps(0, 3, coords_empty,child_sequence_with_gaps,  0) == 3);
  fail_unless( get_window_end_coordinates_excluding_gaps(0, 3, coords_one,  child_sequence_with_gaps,  1) == 4);
	fail_unless( get_window_end_coordinates_excluding_gaps(1, 3, coords_one,  child_sequence_with_gaps,  1) == 5);
  fail_unless( get_window_end_coordinates_excluding_gaps(1, 3, coords_odd,  child_sequence_with_gaps,  3) == 5);
  fail_unless( get_window_end_coordinates_excluding_gaps(3, 3, coords_odd,  child_sequence_with_gaps,  3) == 6);
  fail_unless( get_window_end_coordinates_excluding_gaps(5, 3, coords_odd,  child_sequence_with_gaps,  3) == 8);
  fail_unless( get_window_end_coordinates_excluding_gaps(0, 3, coords_odd,  child_sequence_with_gaps,  3) == 4);
  fail_unless( get_window_end_coordinates_excluding_gaps(2, 3, coords_odd,  child_sequence_with_gaps,  3) == 5);
  fail_unless( get_window_end_coordinates_excluding_gaps(4, 3, coords_odd,  child_sequence_with_gaps,  3) == 7);
  fail_unless( get_window_end_coordinates_excluding_gaps(1, 3, coords_even, child_sequence_with_gaps,  8) == 5);
  fail_unless( get_window_end_coordinates_excluding_gaps(3, 3, coords_even, child_sequence_with_gaps,  8) == 6);
  fail_unless( get_window_end_coordinates_excluding_gaps(5, 3, coords_even, child_sequence_with_gaps,  8) == 9);
  fail_unless( get_window_end_coordinates_excluding_gaps(7, 3, coords_even, child_sequence_with_gaps,  8) == 11);
  fail_unless( get_window_end_coordinates_excluding_gaps(9, 3, coords_even, child_sequence_with_gaps,  8) == 12);
  fail_unless( get_window_end_coordinates_excluding_gaps(0, 3, coords_even, child_sequence_with_gaps,  8) == 4);
  fail_unless( get_window_end_coordinates_excluding_gaps(2, 3, coords_even, child_sequence_with_gaps,  8) == 5);
  fail_unless( get_window_end_coordinates_excluding_gaps(4, 3, coords_even, child_sequence_with_gaps,  8) == 7);
  fail_unless( get_window_end_coordinates_excluding_gaps(6, 3, coords_even, child_sequence_with_gaps,  8) == 10);
  fail_unless( get_window_end_coordinates_excluding_gaps(8, 3, coords_even, child_sequence_with_gaps,  8) == 11);
	
}
END_TEST

START_TEST (check_find_number_of_snps_in_block)
{
  int coords_empty[0] = {};
  int coords_even[8]  = {1,3,5,7,11,13,17,19};
	char *child_sequence = "";
	
	fail_unless( find_number_of_snps_in_block(1,3,  coords_empty, child_sequence, 8) == 0);
	fail_unless( find_number_of_snps_in_block(2,2,  coords_even, child_sequence, 8) == 0);
	fail_unless( find_number_of_snps_in_block(1,3,  coords_even, child_sequence, 8) == 1);
  fail_unless( find_number_of_snps_in_block(1,4,  coords_even, child_sequence, 8) == 2);
  fail_unless( find_number_of_snps_in_block(1,19, coords_even, child_sequence, 8) == 7);
  fail_unless( find_number_of_snps_in_block(0,20, coords_even, child_sequence, 8) == 8);
	
}
END_TEST

Suite * check_snp_searching_suite (void)
{
  Suite *s = suite_create ("snp_searching");

  TCase *tc_snp_searching = tcase_create ("snp_searching");
  tcase_add_test (tc_snp_searching, check_find_starting_index_windows );
	tcase_add_test (tc_snp_searching, check_advance_window_start_to_next_snp);
	tcase_add_test (tc_snp_searching, check_rewind_window_end_to_last_snp);
	tcase_add_test (tc_snp_searching, check_get_window_end_coordinates_excluding_gaps);
	tcase_add_test (tc_snp_searching, check_find_number_of_snps_in_block);
  suite_add_tcase (s, tc_snp_searching);

  return s;
}
