## Comados UNIX

- `pwd`: Imprime en pantalla la ruta exacta (absoluta) de la carpeta donde te encuentras actualmente.
- cd: Sirve para moverte a otro directorio. Un truco clave: usar `cd ..` te lleva al "directorio padre", es decir, una carpeta hacia atrás.
- `ls`: Lista los contenidos de un directorio, ofrece información sobre los ficheros. Tiene modificadores como:
  - -l Formato largo. Muestra una lista detallada on los permisos, el dueño, el tamaño y la fecha de modificación de cada archivo.
  - -t Ordenado por tiempo de acceso, ordena los archivos por fecha de modificación, mostrando los más nuevos primero.
  - -a Lista todas las entradas. Muestra todos los archivos, incluyendo los que están ocultos.
  - -s En tamaño de bloques, muestra el tamaño de cada archivo en bloques.
  - -d Información sobre el estado del directorio
  - -r En orden inverso.
  - -v Según último acceso, ordena según la última vez que se accedió(se abrió o se leyó) el archivo.
  - -R Lista de manera recursiva todos los subdirectorios que encuentre, es decir, no solo te muestra lo que hay en tu carpeta actual, sino que entra de forma automática en cada subcarpeta que encuentre y te muestra su contenido también.

- `mkdir`: Crea una carpeta vacia con el nombre que indiquemos.
- `rmdir`: Elimina una carpeta. **Solo si está vacía**.
- `cat`: Muestra todo el contenido de un archivo muy grande de texto de golpe en pantalla.
- `more`: Si el archivo es muy largo, este comando permite leerlo poco a poco, página a página.
- `rm`: Borra un archivo de forma permanente.
- `rmdir`: Elimina el directorio especificado, simpre y cuando este vacío.
- `cp`: Copia el directorio de origen en el destino especificado.

```bash
cp ~/Downloads/"libro de inglés.pdf" ~/Desktop/prueba/
```

- `mv`: Mueve un archivo a otra ubicación.

```bash
mv ~/Downloads/"libro de inglés.pdf" ~/Documents/prueba/
```

- `who`: Muestra una lista de usuarios que están conectados al sistema en ese momento.
- `cal`: Muestra un calendario por pantalla.
- `bc`: Abre una calculadora de la línea de comandos.
- `du`: Nos dice cuanto espacio exacto está ocupando un archivo o carpeta específica.
- `df`: Informa sobre el espacio libre en el sistema.
- `ps`: Lista los procesos o programas que se están ejecutando. Con -f obtenemos un listado completo y con -e vemos los procesos de todos los usuarios, -l genera un listado largo.
-
