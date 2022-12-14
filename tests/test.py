import sys
import os
import subprocess
import numpy as np

proc = subprocess.Popen("./cinema", shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
(out_string, err_string) = proc.communicate()

print(os.listdir())
# Проверяем вывод ошибку, если файл пуст
if os.stat('../films.txt').st_size == 0 and 'Ошибка: файл пуст.' in out_string.decode('utf-8').strip():
    print('Test passed! File is empty.')
    sys.exit(0)

# Проверяем содержатся ли в выводе все строки с фильмами из films.txt
out = [s.decode("utf-8") for s in out_string.split(b"\n") if (len(s) > 0)]
with open('../films.txt', 'r') as file:
    data = file.read().split('\n')
    result = np.in1d(data, out[:len(data)])
    if False in result:
        print('Test failed! Data in stdout of C have difference with data from file.')
        sys.exit(1)
    else:
        print('Test passed!')
        sys.exit(0)
