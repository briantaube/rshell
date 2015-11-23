Brian Taube
##rshell README

rshell is an expanded shell program that runs on top of bash.

rhsell provides its own prompt listing the username and host it is running on.  Multiple commands can be entered in one line if they are separated by a semi-   colon.

    ex: ls;echo this is a second command on the same line!

When multiple commands on the same line are separated by a double ampersand or  double pipe they can be executed conditionally based on the success of the      previous command.

    && - executes the following command only if the first command succeeded
    || - executes the following command only if the first command failed

    examples:
    ls&&mkdir test&&ls&&rmdir test&&ls
    ls-||echo the first command failed!

To exit rshell simply type 'exit'. This can also be included as part of a       multiple command chain.

Comments may be included in the command chain by using the hash symbol '#'.     Anything after the hash symbol will be regarded as a comment until the next fullcommand separated by a semi-colon.

    examples:
    echo this part will print # this part will not!
    echo this will print#this won't;echo but this will.

To exit rshell simply type exit. This can also be included as part of a multiplecommand chain.

    examples:
    exit
    echo about to exit...;exit

Known bugs:
1. echo sometimes prints an additional gibberish character
2. ls sometimes fails when part of a multiple command chain
3. ls sometimes displays a '?' after created directories. This '?' character is not actually part of the directory name.
4. Only allows for chains of 9 commands
5. Only allows for 9 semi-colon seperated chains of commands

#Copyright (C)  2015  Brian Taube.
    Permission is granted to copy, distribute and/or modify this document
    under the terms of the GNU Free Documentation License, Version 1.3
    or any later version published by the Free Software Foundation;
    with no Invariant Sections, no Front-Cover Texts, and no Back-Cover Texts.
    A copy of the license is included in the section entitled "GNU
    Free Documentation License".
