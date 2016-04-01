# Copyright 2016, The libsigc++ Development Team
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

enable_testing ()

set (TEST_SOURCE_FILES
  test_accum_iter.cc
  test_accumulated.cc
  test_bind_as_slot.cc
  test_bind.cc
  test_bind_ref.cc
  test_bind_refptr.cc
  test_bind_return.cc
  test_compose.cc
  test_copy_invalid_slot.cc
  test_cpp11_lambda.cc
  test_custom.cc
  test_disconnect.cc
  test_disconnect_during_emit.cc
  test_exception_catch.cc
  test_functor_trait.cc
  test_hide.cc
  test_limit_reference.cc
  test_member_method_trait.cc
  test_mem_fun.cc
  test_ptr_fun.cc
  test_retype.cc
  test_retype_return.cc
  test_signal.cc
  test_signal_move.cc
  test_size.cc
  test_slot.cc
  test_slot_disconnect.cc
  test_slot_move.cc
  test_trackable.cc
  test_trackable_move.cc
  test_track_obj.cc
  test_tuple_cdr.cc
  test_tuple_end.cc
  test_tuple_for_each.cc
  test_tuple_start.cc
  test_tuple_transform_each.cc
  test_visit_each.cc)

function (add_sigcpp_test TEST_SOURCE_FILE)
	get_filename_component (test_name ${TEST_SOURCE_FILE} NAME_WE)
	add_executable (${test_name} ${TEST_SOURCE_FILE} testutilities.cc)
	target_link_libraries (${test_name} sigc-${SIGCXX_API_VERSION})
	add_test (${test_name} ${CMAKE_CURRENT_BINARY_DIR}/${test_name})
endfunction (add_sigcpp_test)

foreach (test_file ${TEST_SOURCE_FILES})
	add_sigcpp_test (${test_file})
endforeach()