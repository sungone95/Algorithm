package a0314;
import java.util.*;
import java.io.*;
/*
 현재위치에서 아래 오른쪽으로 숫자만큼 갈수있으면 가고 못가면 끝냄 
 위치가 (n-1,n-1)이면 cnt증가, 
 반복문 다 돌리고 cnt 출력 
 
 -> 이렇게 푸니까 시간초과 걸림 
 -> dp 로 풀어야하나?
 */
public class B1890점프 {
	
	static int[][] arr;
	static int size ;
	static int cnt = 0;
	
	static int[] di = {0, 1};
	static int[] dj = {1, 0};
	
	static boolean check(int i, int j) {
		if(0<=i&&i<size && 0<=j&&j<size)return true;
		return false;
	}
	
	static void findall(int i, int j) {
		
		if(i==size-1 && j==size-1) {
			cnt++;
			return;
		}
		
		for(int d=0; d<2; d++) {
			int len = arr[i][j];
			int ni = i+di[d]*len;
			int nj = j+dj[d]*len;
			
			if(check(ni,nj))findall(ni,nj);
		}
		
		
	}
	
	public static void main(String[] args) throws Exception{
		
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		size = Integer.parseInt(br.readLine());
		arr = new int[size][size];
		
		for(int i=0; i<size; i++) {
			StringTokenizer ST = new StringTokenizer(br.readLine());
			for(int j=0; j<size; j++) {
				arr[i][j] = Integer.parseInt(ST.nextToken());
			}
		}
		
		findall(0,0);
		
		System.out.println(cnt);

	}

}
