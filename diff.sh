#!bin/bash
make
./Container vector > ft_container
./Container_std vector > std_container
diff ft_container std_container
echo "Diff done"
