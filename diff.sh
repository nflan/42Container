#!bin/bash
make
dir=tests
rm -fr $dir
mkdir $dir

#STACK
\time -f "Total time: %E" ./Container stack > $dir/ft_stack
\time -f "Total time: %E" ./Container_std stack > $dir/std_stack
diff $dir/ft_stack $dir/std_stack
echo "Diff stack done"

valgrind ./Container stack 1> $dir/_ft_stack 2>> $dir/_ft_stack
valgrind ./Container_std stack 1> $dir/_std_stack 2>> $dir/_std_stack

#VECTOR
\time -f "Total time: %E" ./Container vector > $dir/ft_vector
\time -f "Total time: %E" ./Container_std vector > $dir/std_vector
diff $dir/ft_vector $dir/std_vector
echo "Diff vector done"

valgrind ./Container vector 1> $dir/_ft_vector 2>> $dir/_ft_vector
valgrind ./Container_std vector 1> $dir/_std_vector 2>> $dir/_std_vector

#RBTREE
\time -f "Total time: %E" ./Container map > $dir/ft_map
\time -f "Total time: %E" ./Container_std map > $dir/std_map
diff $dir/ft_map $dir/std_map
echo "Diff rbtree done"

valgrind ./Container map 1> $dir/_ft_map 2>> $dir/_ft_map
valgrind ./Container_std map 1> $dir/_std_map 2>> $dir/_std_map
