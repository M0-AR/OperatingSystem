public class BalanceMonitor implements Runnable{
    private Account account;
    BalanceMonitor(Account account) { this.account = account;}

    @Override
    public void run() {
        String threadName = Thread.currentThread().getName();
        System.out.format("%s started execution%n", threadName);
        while (true) {
            if(account.balance <= 0) {
                // send email, or sms, clouds of smoke ...
                break;
            }
            try {
                Thread.sleep( 1000 );
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            System.out.println(threadName + " is working");
        }
        System.out.format("%s : account has gone too low, email sent, exiting.", threadName);
    }
}






