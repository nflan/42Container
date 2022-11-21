#!bin/bash
make
./Container vector > ft_container
./Container_std vector > std_container
diff ft_container std_container
echo "Diff done"

valgrind ./Container vector 1> _ft_container 2>> _ft_container
valgrind ./Container_std vector 1> _std_container 2>> _std_container
diff ft_container std_container
echo "Diff valgrind done"
