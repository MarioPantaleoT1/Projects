import curses
def startup(window):

    score = open('highscore.txt', 'r')
    highscore = score.readlines()

    # window.addstr(0, 0, str(curses.has_colors()))
    # window.addstr(2, 4, str(curses.has_extended_color_support()))
    window.addstr(1, 1, "  *    .      .   *  .             ..         *           *  .             *")
    window.addstr(2, 1, "*    .      **       ..         *           *  .     *         .          ..")
    window.addstr(3, 6, '[G] Start Game    *   .     .     * .            * .        .      ')
    window.addstr(4, 6, '[H] High Score: ' + highscore[1].strip() + ' [' + highscore[0].strip() + ']   *      .   *  ')
    window.addstr(5, 6, '[Q] Quit    *    .       *        . . *         *      *          *.   ')
    # from patorjk.com
    # from ascii art archive
    window.addstr(6, 1, "   *        .        *    .        *   . ___  . *         . *         . .")
    window.addstr(7, 1, "   .              .    *        .    __,' __`.     *  .        _..----....____")
    window.addstr(8, 1, "  *        .       * .   __...--.'``;.   ,.   ;``--..__   . .'    ,-._    _.-'")
    window.addstr(9, 1, "    ..              _..-''-------'   `'   `'   `'     O ``-''._   (,;') _,'  *")
    window.addstr(10, 1, "      .*         ,'________________                          \\`-._`-','   *")
    window.addstr(11, 1, "           .   *  `._              ```````````------...___   '-.._'-:     . .")
    window.addstr(12, 1, "   .                 ```--.._      ,.                     ````--...__\\-. *")
    window.addstr(13, 1, "          *                  `.--. `-`                       ____    |  |`  * ")
    window.addstr(14, 1, "    .             *        *   `. `.                       ,'`````.  ;  ;`")
    window.addstr(15, 1, " ___                         __   ' '__  _     __________   `.      \\'__/`")
    window.addstr(16, 1, "/ __| __ __ __  __ _   _ _   \\ \\    / / (_)  _ _    __ _____`.     \\  `")
    window.addstr(17, 1, "\\__ \\ \\ V  V / / _` | | ' \\   \\ \\/\\/ /  | | | ' \\  / _` |   `.    \\")
    window.addstr(18, 1, "|___/  \\_/\\_/  \\__,_| |_||_|   \\_/\\_/   |_| |_||_| \\__, |-.   `.   `.___")
    window.addstr(19, 1, " ___    __   __  __ __  __                          |___/    SSt  `------'`")
    window.addstr(20, 1, "|_  )  /  \\  \\ \\/ / \\ \\/ /  * *                .            *           . .")
    window.addstr(21, 1, " / /  | () |  >  <   >  <.           .                *              .  .  ")
    window.addstr(22, 1, "/___|  \\__/  /_/\\_\\ /_/\\_\\                             .           *       ")
    
    ret = 0
    while(True):
        try:
            ret = window.getkey()      
            if(ret == 'q' or ret == 'h' or ret == 'g'):
                break
        except curses.error:
            pass
    return ret