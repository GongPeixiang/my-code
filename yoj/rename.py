import os

for filename in os.listdir('.'):
    if (filename.endswith('.cpp') or filename.endswith('.c')) and filename.startswith('yoj'):
        new_name = 't' + filename[3:]
        os.rename(filename, new_name)
        print(f'Renamed: {filename} -> {new_name}')