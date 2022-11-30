#!bin/bash
make
dir=tests

#COLORS
green='\033[32m'
blue='\033[34m'
yellow='\033[33m'
cyan='\033[36m'
reset='\033[0m'

rm -fr $dir
mkdir $dir

#STACK
echo -e "${cyan}\nSTACK"
\time -f "Total time FT: %E" ./Container stack 20000 > $dir/todel
\time -f "Total time STD: %E" ./Container_std stack 20000 > $dir/todel
./Container stack > $dir/ft_stack
./Container_std stack > $dir/std_stack
diff $dir/ft_stack $dir/std_stack
echo "Diff STACK done"

valgrind ./Container stack 1> $dir/_ft_stack 2>> $dir/_ft_stack
valgrind ./Container_std stack 1> $dir/_std_stack 2>> $dir/_std_stack

#VECTOR
echo -e "${yellow}\nVECTOR"
\time -f "Total time FT: %E" ./Container vector 20000 > $dir/todel
\time -f "Total time STD: %E" ./Container_std vector 20000 > $dir/todel
./Container vector > $dir/ft_vector
./Container_std vector > $dir/std_vector
diff $dir/ft_vector $dir/std_vector
echo "Diff VECTOR done"

valgrind ./Container vector 1> $dir/_ft_vector 2>> $dir/_ft_vector
valgrind ./Container_std vector 1> $dir/_std_vector 2>> $dir/_std_vector

<<<<<<< HEAD
#MAP
echo -e "${green}\nMAP"
\time -f "Total time FT: %E" ./Container map 20000 > $dir/todel
\time -f "Total time STD: %E" ./Container_std map 20000 > $dir/todel
./Container map > $dir/ft_map
./Container_std map > $dir/std_map
diff $dir/ft_map $dir/std_map
echo "Diff MAP done"

valgrind ./Container map 1> $dir/_ft_map 2>> $dir/_ft_map
valgrind ./Container_std map 1> $dir/_std_map 2>> $dir/_std_map

#SET
echo -e "${blue}\nSET"
\time -f "Total time FT: %E" ./Container 'set' 20000 > $dir/todel
\time -f "Total time STD: %E" ./Container_std 'set' 20000 > $dir/todel
./Container 'set' > $dir/ft_set
./Container_std 'set' > $dir/std_set

diff $dir/ft_set $dir/std_set
echo "Diff SET done"

valgrind ./Container 'set' 1> $dir/_ft_set 2>> $dir/_ft_set
valgrind ./Container_std 'set' 1> $dir/_std_set 2>> $dir/_std_set

rm $dir/todel
=======
#RBTREE
\time -f "Total time: %E" ./Container rbtree > $dir/ft_rbtree
\time -f "Total time: %E" ./Container_std rbtree > $dir/std_rbtree
diff $dir/ft_rbtree $dir/std_rbtree
echo "Diff rbtree done"

valgrind ./Container rbtree 1> $dir/_ft_rbtree 2>> $dir/_ft_rbtree
valgrind ./Container_std rbtree 1> $dir/_std_rbtree 2>> $dir/_std_rbtree
>>>>>>> a903954 (Clean)
