package a0314;

import java.io.*;
import java.util.*;
/*
 
  dfs처럼 풀었을때 문제점 -> 중복되는 연산이 생긴다 
  중복되는연산을 어떻게 줄일까?
  -> 값을 저장하는 배열을 하나 만든다. 
  -> 큐를 이용하여 값 저장 
  
  -> 실수한 부분 끝지점 나오면 큐에서 break; 걸어서 나오게 짰는데 
  마지막 지점 도착했다고 해서 이전에 경우의수가 없는게 아님
  -> 왜인지 생각해볼것
  
 */
public class B1890점프_두번째풀이 {

	public static void main(String[] args) throws Exception{
		
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int size = Integer.parseInt(br.readLine());
		
		int[][] arr = new int[size][size];
		long[][] record = new long[size][size];
		record[0][0] = 1;
		
		for(int i=0; i<size; i++) {
			StringTokenizer ST = new StringTokenizer(br.readLine());
			for(int j=0; j<size; j++) {
				arr[i][j] = Integer.parseInt(ST.nextToken());
			}
		}
		
		
		int[] di = {0, 1};
		int[] dj = {1, 0};
		
		for(int i=0; i<size; i++) {
			for(int j=0; j<size; j++) {
				if(record[i][j]==0 || (i==size-1&&j==size-1))continue;
				
				//System.out.println("i:"+i+" j:"+j);
				for(int d=0; d<2; d++) {
					int len = arr[i][j];
					int ni = i+di[d]*len;
					int nj = j+dj[d]*len;
					
					if(0<=ni&&ni<size && 0<=nj&&nj<size) {
						record[ni][nj]+=record[i][j];			//값 더하기
					}
				}
//				for(long[]tmp : record)System.out.println(Arrays.toString(tmp));
//				System.out.println();
			}
		}
			

		
		
		System.out.println(record[size-1][size-1]);
		
	}

}
