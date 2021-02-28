# UniqueLex

This scanner can generate a unique list of every word in a file. If your permissions suffice, you can scan a drive with the following pipeline:

    cat /dev/sda2 | ./lexer | ./uniquelex > dumpfile

if you want to scan multiple drives:

    { cat /dev/sda2; cat /dev/sdb2; } | ./lexer | ./uniquelex > dumpfile

You can edit lexer.c to define valid characters and word size.

This can be used for generating dictionaries for Hashcat. It will also scan deleted data assuming the data hasn't already been overwritten.

The AVL tree is from https://github.com/ebiggers/avl_tree
