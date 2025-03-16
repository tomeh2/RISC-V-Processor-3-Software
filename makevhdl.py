import sys

print("Running makevhdl...")

filename_src = sys.argv[1]
target_mem_size = int(sys.argv[2])

with open(filename_src, mode = 'rb') as file_src:
    curr_byte = file_src.read()

filename_target = filename_src.split('.')[0]
filename_target += '.vhd'

print('filename_src: ', filename_src)
print('filename_targer: ', filename_target)

with open(filename_target, "w") as file_target:
    file_target.write("library IEEE;\n")
    file_target.write("use IEEE.STD_LOGIC_1164.ALL;\n")
    file_target.write("\n")
    file_target.write("package rom_init is\n")
    file_target.write("\ttype T_rom is array (0 to %d) of std_logic_vector(31 downto 0);\n" % (target_mem_size / 4 - 1))
    file_target.write("\tconstant C_rom_init: T_rom := (\n")

    for i in range(0, int(len(curr_byte) / 4), 1):
        file_target.write("\t\t%d => X\"%02x%02x%02x%02x\",\n" % (i, curr_byte[i * 4 + 3], curr_byte[i * 4 + 2], curr_byte[i * 4 + 1], curr_byte[i * 4]))
    file_target.write("\t\tothers => X\"00000000\");\n")

    file_target.write("end package rom_init;\n")

print("ROM Usage: %d of %d bytes (%d%% full)" % (len(curr_byte), target_mem_size, len(curr_byte) / target_mem_size * 100))