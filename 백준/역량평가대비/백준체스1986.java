package a0314;

import java.util.*;
import java.io.*;

/*
 입력받고 말 종류별로 좌표 list에 저장 해놓고 각각 안전하지않은 영역 모두 -1로 처리 
 
 퀸 -> 가로, 세로, 대각선으로 쭉 이동가능, 장애물 만나면 더이상 못감
 나이트 -> 거리 3이동 가능하고 x,y좌표 둘다 겹치지 않는곳만 가능
 폰 -> 그냥 장애물 역할
 
 */

public class 백준체스1986 {

	static int sero ;
	static int garo ;
	static int[][] arr;
	
	static boolean check(int i, int j) {
		if(1<=i&&i<=sero && 1<=j&&j<=garo)return true;
		return false;
	}
	
	static int[] di = {-1, -1, 0, 1, 1, 1, 0, -1};
	static int[] dj = {0, 1, 1, 1, 0, -1, -1, -1};		//퀸을 위한 8방탐색 
	
	static void qcheck(int i, int j) {			//퀸의 이동경로 에 -1 처리
		
		for(int d=0; d<8; d++) {
			
			int ni = i;	int nj = j;
			while(true) {
				ni+=di[d];	nj+=dj[d];
				
				if(check(ni,nj) && (arr[ni][nj]==0 || arr[ni][nj]==-1)) {
					if(arr[ni][nj]==0)arr[ni][nj] = -1;
				}else break;
			}
		}
	}
	
	static int[] ki = {-2, -2, -1,-1, 1, 1, 2, 2};
	static int[] kj = {1, -1, 2, -2, 2, -2, 1, -1};
	
	static void kcheck(int i, int j) {		//나이트의 이동경로 
		
		for(int d=0; d<8; d++) {
			int ni = i+ki[d];
			int nj = j+kj[d];
			
			if(check(ni, nj)&&arr[ni][nj]==0)arr[ni][nj] = -1;
		}
	}
	
	
	public static void main(String[] args) throws Exception{
		
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		StringTokenizer ST = new StringTokenizer(br.readLine());
		
		sero = Integer.parseInt(ST.nextToken());
		garo = Integer.parseInt(ST.nextToken());
		
		arr = new int[sero+1][garo+1];
		
		ST = new StringTokenizer(br.readLine());			//2번째줄
		int queennum = Integer.parseInt(ST.nextToken());
		
		for(int i=0; i<queennum; i++) {
			int qi = Integer.parseInt(ST.nextToken());
			int qj = Integer.parseInt(ST.nextToken());
			
			arr[qi][qj] = 1;
		}
		
		ST = new StringTokenizer(br.readLine());			//3번째줄
		int knightnum = Integer.parseInt(ST.nextToken());
		
		for(int i=0; i<knightnum; i++) {
			int ki = Integer.parseInt(ST.nextToken());
			int kj = Integer.parseInt(ST.nextToken());
			
			arr[ki][kj] = 2;
		}
		
		ST = new StringTokenizer(br.readLine());			//4번째줄
		int pawnnum = Integer.parseInt(ST.nextToken());
		
		for(int i=0; i<pawnnum; i++) {
			int pi = Integer.parseInt(ST.nextToken());
			int pj = Integer.parseInt(ST.nextToken());
			
			arr[pi][pj] = 3;
		}
		
		for(int i=1; i<=sero; i++) {
			for(int j=1; j<=garo; j++) {
				if(arr[i][j]==1) {					//퀸일때
					qcheck(i, j);
				}else if(arr[i][j]==2) {			//나이트 일때
					kcheck(i, j);
				}
			}
		}
		
		int cnt = 0;
		for(int i=1; i<=sero; i++) {
			for(int j=1; j<=garo; j++) {
				if(arr[i][j]==0)cnt++;
			}
		}
//		for(int i=1; i<=sero; i++) {
//			for(int j=1; j<=garo; j++) {
//				System.out.print(arr[i][j]+" ");
//			}
//			System.out.println();
//		}
		
		System.out.println(cnt);
		
	}

}
