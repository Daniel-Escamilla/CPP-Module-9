#!/bin/bash

echo "Nombre del ejecutable (por defecto: a.out):"
read EXEC_NAME
EXEC_NAME=${EXEC_NAME:-a.out}

echo "Archivos a compilar (separados por espacio, por defecto: main.cpp):"
read FILES
FILES=${FILES:-main.cpp}

echo "¿Archivos .hpp adicionales a crear en include/ (separados por espacio)? [Deja vacío si no]:"
read EXTRA_HPP

echo "¿Quieres añadir archivos .tpp (uno por cada .hpp)? [y/N]:"
read ADD_TPP
ADD_TPP=${ADD_TPP:-n}

SRC_DIR="src"
INCLUDE_DIR="include"
OBJ_DIR="${EXEC_NAME}_objects"
mkdir -p $SRC_DIR $INCLUDE_DIR $OBJ_DIR

FIRST_HPP=$(echo $EXTRA_HPP | awk '{print $1}')

# Crear .hpp (y .tpp si se desea)
for hpp in $EXTRA_HPP; do
  HEADER_GUARD=$(echo ${hpp%.*} | tr 'a-z' 'A-Z')_HPP
  TPP_NAME="${hpp%.hpp}.tpp"

  cat > $INCLUDE_DIR/$hpp <<EOL
#ifndef $HEADER_GUARD
# define $HEADER_GUARD


#endif // $HEADER_GUARD
EOL

  if [[ "$ADD_TPP" == "y" || "$ADD_TPP" == "Y" ]]; then
    # Añadir include al principio del .tpp
    echo "#include \"$hpp\"" > $INCLUDE_DIR/$TPP_NAME
  fi
done
# Crear archivos fuente
for src in $FILES; do
  cat > $SRC_DIR/$src <<EOL
#include "../include/$FIRST_HPP"


EOL
done

# Lista de archivos fuente para el Makefile
SRC_LIST=""
for src in $FILES; do
  SRC_LIST="$SRC_LIST    $SRC_DIR/$src \\
"
done

# Crear Makefile
cat > Makefile <<EOL
NAME = $EXEC_NAME
CC = g++
CFLAGS = -g3 -Wall -Wextra -Werror -std=c++98

SRC =	$SRC_LIST

OBJS = \$(notdir \$(SRC:.cpp=.o))
OBJDIR = $OBJ_DIR

all: \$(OBJDIR) \$(NAME)

\$(NAME): \$(addprefix \$(OBJDIR)/, \$(OBJS))
	\$(CC) \$(CFLAGS) -o \$@ \$(addprefix \$(OBJDIR)/, \$(OBJS))

\$(OBJDIR)/%.o: src/%.cpp | \$(OBJDIR)
	\$(CC) \$(CFLAGS) -c \$< -o \$@

\$(OBJDIR):
	mkdir -p \$(OBJDIR)

clean:
	rm -rf \$(OBJDIR)

fclean: clean
	rm -f \$(NAME)

re: fclean all

.PHONY: all clean fclean re
EOL

# .gitignore
cat > .gitignore <<EOL
.vscode
$EXEC_NAME
$OBJ_DIR/
EOL

rm -- "$0"
