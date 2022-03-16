package a0315;

import java.util.*;
import java.io.*;

/*
 set을 이용한 dfs 문제인듯?
 5*5 배열의 모든 좌표에서 dfs를 적용하여 원소들을 더해가며 
 문자열을 만든다. 
 cnt가 6이되면 set의 key값으로 비교하고 있으면 return 
 없으면 추가 -> 다돌고 set의 사이즈를 출력하면 됟듯?
 
 
 */

public class B2210숫자판점프 {

	static Set<String> set = new HashSet<>();
	static int[][] arr = new int[5][5]; 
	static int[][] visit;
	
	
	static int[] di = {-1, 0, 1, 0};
	static int[] dj = {0, 1, 0, -1};
	
	static boolean check(int i, int j) {
		if(0<=i&&i<5 && 0<=j&&j<5)return true;
		return false;
	}
	
	static void dfs(int i, int j, int len, String st) {
		
		if(len == 6) {
			if(!set.contains(st))set.add(st);
			return;
		}
		
		for(int d=0; d<4; d++) {
			int ni = i+di[d];
			int nj = j+dj[d];
			
			if(check(ni, nj))dfs(ni, nj, len+1, st+arr[ni][nj]);
		}
	}
	
	
	
	public static void main(String[] args) throws Exception{
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

		for(int i=0; i<5; i++) {
			StringTokenizer ST = new StringTokenizer(br.readLine());
			for(int j=0; j<5; j++) {
				arr[i][j] = Integer.parseInt(ST.nextToken());
			}
		}
		
		for(int i=0; i<5; i++) {
			for(int j=0; j<5; j++) {
				dfs(i, j, 1, Integer.toString(arr[i][j]));
			}
		}
		
		//System.out.println(set);
		
		System.out.println(set.size());
	}

}
