import java.util.Scanner;

/*
    Keeps a circular queue of players implemented by a linked list.
    When given time exceeds the reflex time of the player a passover of the pillow occurs.
    Pops next player in queue and puts the player to the last of the queue.
    Updates the next time of pass.
    If forward pass is enables, next player is taken from the front
 */
public class PillowGame {

    /*
        Pillow Game operation codes
     */
    public static final char MUSIC_END = 'M';
    public static final char REVERSE = 'R';
    public static final char NEW_PLAYER = 'I';
    public static final char PRINT = 'P';
    public static final char END = 'F';

    private final Linked_List<Player> playerQ;

    /*
        The time starting from when the pillow will be
        on the possession of the next player in queue.
     */
    private int nextTimeOfPassOver;

    /*
        Whether the queue will proceed from the first player onward
        or from the last player backward.
     */
    private boolean isForwardPass;

    /*
        When new player is added, the next id is taken and the field is
        incremented.
     */
    private int lastPlayerId;

    public PillowGame(int[] reflexes) {
        this.playerQ = new Linked_List<>();
        this.lastPlayerId = 0;

        for (int i = 0; i < reflexes.length; i++) {
            playerQ.add(new Player(i + 1, reflexes[i]));
            this.lastPlayerId++;
        }

        this.isForwardPass = true;
        this.nextTimeOfPassOver = this.playerQ.getFirstElement().reflex + 1;
    }

    public int getNumPlayers() {
        return playerQ.size();
    }

    /*
        Circulates the queue and moves next time of pass over in such way
        that the time variable in the argument is in the range [currentTime, nextTimeOfPassOver).
        Which results in the immediate player on queue to be the pillow holder.
     */
    private void setGameStatusToCurrentTime(int time) {
        while (this.nextTimeOfPassOver <= time) {
            passOver();
        }
    }

    private void passOver() {
        Player nextPlayerInQ;
        if (this.isForwardPass) {
            this.playerQ.add(this.playerQ.popFirstElement());
            nextPlayerInQ = this.playerQ.getFirstElement();
        } else {
            this.playerQ.add(0, this.playerQ.popLastElement());
            nextPlayerInQ = this.playerQ.getLastElement();
        }
        this.nextTimeOfPassOver += nextPlayerInQ.reflex;
    }

    /*
        Pops player from queue and does not add to last, therefore eliminating the
        player.
        nextTimeOfPassOver is updated according to the new player's reflex.

        Pass over takes 1 second time. Meaning that the time provided as the argument
        will be used to change to the next player. The next players time will start from
        time + 1. Although after elimination the next player will hold the pillow at time,
        but his interval will start from time + 1.
     */
    public String endMusic(int time) {
        setGameStatusToCurrentTime(time);

        Player eliminatedPlayer;
        if (this.isForwardPass) {
            eliminatedPlayer = this.playerQ.popFirstElement();
            this.nextTimeOfPassOver = time + 1 + this.playerQ.getFirstElement().reflex;
        } else {
            eliminatedPlayer = this.playerQ.popLastElement();
            this.nextTimeOfPassOver = time + 1 + this.playerQ.getLastElement().reflex;
        }

        return "Player " + eliminatedPlayer.id + " has been eliminated at t=" + time;
    }

    /*
        If reverse pass is activated, the last player in the linked list becomes
        the one holding the pillow. So upon reversal from forward pass, the first player
        needs to be appended to the last to make it the pillow holder.

        Same for forward pass from reverse pass.
     */
    public void reverse(int time) {
        setGameStatusToCurrentTime(time);

        this.isForwardPass = !this.isForwardPass;

        if (this.isForwardPass) {
            this.playerQ.add(0, this.playerQ.popLastElement());
        } else {
            this.playerQ.add(this.playerQ.popFirstElement());
        }
    }

    public void addNewPlayer(int time, int reflex) {
        setGameStatusToCurrentTime(time);

        if (this.isForwardPass) {
            this.playerQ.add(new Player(++this.lastPlayerId, reflex));
        } else {
            this.playerQ.add(0, new Player(++this.lastPlayerId, reflex));
        }
    }

    public String getPlayerHoldingPillow(int time) {
        setGameStatusToCurrentTime(time);

        Player currentPlayer = this.isForwardPass ?
                this.playerQ.getFirstElement() : this.playerQ.getLastElement();

        return "Player " + currentPlayer.id + " is holding the pillow at t=" + time;
    }

    public String getGameOverStatus(int time) {
        StringBuilder stringBuilder = new StringBuilder("Game over: ");
        if (this.playerQ.size() == 1) {
            stringBuilder.append("Player ")
                    .append(this.playerQ.getFirstElement()).append(" wins!!");
        } else {
            stringBuilder.append(getPlayerHoldingPillow(time))
                    .append(", pillow passing sequence = Player ")
                    .append(getPlayerPassSequence());
        }

        return stringBuilder.toString();
    }

    /*
        Gets the cycle of passing as a string.
     */
    private String getPlayerPassSequence() {
        StringBuilder stringBuilder = new StringBuilder();
        if (this.isForwardPass) {
            final Player start = this.playerQ.getFirstElement();

            while (true) {
                stringBuilder.append(this.playerQ.getFirstElement().id);

                this.playerQ.add(this.playerQ.popFirstElement());

                if (this.playerQ.getFirstElement().id != start.id) {
                    stringBuilder.append(", ");
                } else {
                    break;
                }
            }
        } else {
            final Player start = this.playerQ.getLastElement();

            while (true) {
                stringBuilder.append(this.playerQ.getLastElement().id);

                this.playerQ.add(0, this.playerQ.popLastElement());

                if (this.playerQ.getLastElement().id != start.id) {
                    stringBuilder.append(", ");
                } else {
                    break;
                }
            }
        }
        return stringBuilder.toString();
    }

    private static class Player {
        private final int id;
        private final int reflex;

        public Player(int id, int reflex) {
            this.id = id;
            this.reflex = reflex;
        }

        @Override
        public String toString() {
            return String.valueOf(this.id);
        }
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int numPlayers = scanner.nextInt();
        scanner.nextLine();
        int[] reflexes = new int[numPlayers];
        for (int i = 0; i < numPlayers; i++) {
            reflexes[i] = scanner.nextInt();
        }

        PillowGame pillowGame = new PillowGame(reflexes);

        boolean isGameOver = false;
        int inputTime;
        do {
            inputTime = scanner.nextInt();
            char command = scanner.next().charAt(0);

            switch (command) {
                case PillowGame.MUSIC_END:
                    System.out.println(pillowGame.endMusic(inputTime));
                    break;
                case PillowGame.REVERSE:
                    pillowGame.reverse(inputTime);
                    break;
                case PillowGame.NEW_PLAYER:
                    int reflex = scanner.nextInt();
                    pillowGame.addNewPlayer(inputTime, reflex);
                    break;
                case PillowGame.PRINT:
                    System.out.println(pillowGame.getPlayerHoldingPillow(inputTime));
                    break;
                case PillowGame.END:
                    isGameOver = true;
                    break;
                default:

            }

            scanner.nextLine();

            if (pillowGame.getNumPlayers() == 1) {
                isGameOver = true;
            }
        } while (!isGameOver);

        // print game over status
        System.out.println(pillowGame.getGameOverStatus(inputTime));
    }
}
