#! /bin/bash
#Generate a list of words ordered by frequency

#cat ${1:? "Missing input file argument"}            |  \          Cat the file passed as the first argument or print error message if no argument was provided.
#    tr " " "\n"                                     |  \          Replace spaces by newlines. This puts every word on its own line.
#    tr -d {$2:-'.,?!<>(){}[]1234567890/"+=_/'\\\'}  |  \          Remove special characters.
#    sed '/^$/d'                                     |  \          Remove empty lines.
#    sort                                            |  \          Sort list alphabetically for uniq can count frequencies.
#    uniq -c                                         |  \          Count word frequency. Word frequency is added to the beginning of each line.
#    uniq -u                                         |  \          Remove repeated lines.
#    sort -r                                         |  \          Sort lines again. This times lines are sorted by the frequency number that was added before!
#    tr  -d \ 1234567890                                           Remove digits to leave us with just the list of words ordered by frequency.

cat ${1:? "Missing input file argument"}            |  \
    tr " " "\n"                                     |  \
    tr -d {$2:-'.,?!<>(){}[]1234567890/"+=_/'\\\'}  |  \
    sed '/^$/d'                                     |  \
    sort                                            |  \
    uniq -c                                         |  \
    uniq -u                                         |  \
    sort -r                                         |  \
    tr  -d \ 1234567890

