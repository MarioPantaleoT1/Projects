Authored by: Mario Pantaleo and Jake Butler\n
To use our Memory Leak analysis tool, simply run the following command in the command prompt:

python tool.py <your filepath here>

OR 

python3 tool.py <your filepath here>

Source code of the tool can be found in tool.py itself. The output file will be populated with a representation of the graph, its program point translation to the file itself, and a "stacktrace"-ish printout of what variables are defined at certain graph nodes. Test cases are located in the "test_cases/" directory
