//author Ertuğrul Demir - ID: 260201059

import java.io.*;
import java.util.ArrayList;
import java.util.PriorityQueue;


public class MaxHeapWithPriorityQueue {

    public static void main(String args[]) {
        // create priority queue
        PriorityQueue<Integer> prq = new PriorityQueue<>((a,b)->b-a);

        //Read File

        String line;
        ArrayList<Integer> str = new ArrayList<>();
        try {
            File file = new File("C:\\Users\\Ertugrul Demir\\Desktop\\Desktop\\CLion_Project\\list.txt");
            BufferedReader b = new BufferedReader(new FileReader(file));
            while ((line = b.readLine()) != null) {
                for (String s : line.split(" ")) {
                    str.add(Integer.parseInt(s));
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

        //Setting Priority Queue and time calculation
        long startTime = System.currentTimeMillis();
        //Clock
        for (Integer i : str){
            prq.add(i);
        }
        //Clock
        long stopTime = System.currentTimeMillis();
        System.out.println("Elapsed time was " + (stopTime - startTime) + " milliseconds.");

        //Write a file

        try {
            FileWriter writer = new FileWriter("MyFile.txt", true);
            for (Integer j : prq) {
                writer.write(Integer.toString(j));
                writer.write(" ");
            }
            writer.close();
        } catch (IOException e) {
            e.printStackTrace();
        }

    }

}
