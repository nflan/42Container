#!bin/bash
if [ ! -f Container ]
then
	make
fi
./Container vector > ft_container
./Container_std vector > std_container
diff ft_container std_container
