# BA-Project2

Firstly:
    The main class (songDatabase) is meant to handle every interaction
    with the database itself. The nested class (songEntry) is hidden
    because all interaction goes through songDatabase; this is good
    practice as far as I know, but inconvenient for testing. Didn't really
    think that through.

    The field groupName is optional because an individual artist isn't
    necessarily part of a group.

Secondly:
    Initial tests written.

Thirdly:
    Implementation written; output was significantly different from expected
    output.

    Expected:

    Tracklist:
    	No songs.

    >Ode to Joy
    		Beethoven

    Songs by Beethoven:
    >Ode to Joy

    Tracklist:

    >Ode to Joy
    		Beethoven
    >That's Classic
    	Group name: The Bs
    		Bach
    		Beethoven

    Songs by Beethoven:
    >Ode to Joy
    >That's Classic (with Bach)

    Songs by Bach:
    >That's Classic (with Beethoven)

    Songs by Brahms:
    >No songs.

    (I put this here to back me up re: the fact that I did write tests, even)
    though the output has to be checked by hand.

Fourthly:
    I didn't have test cases at all for reading/writing to files, because that
    was something I thought of during implementation.

    Output should be:

    Tracklist:

    >Ode to Joy
            Beethoven
    >That's Classic
        Group name: The Bs
            Bach
            Beethoven

    for both databases. This did not work on the first try either.

