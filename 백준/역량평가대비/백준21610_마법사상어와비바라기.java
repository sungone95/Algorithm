package a0324;

import java.util.*;
import java.io.*;

public class 백준21610_마법사상어와비바라기 {

	static int[][] arr;
	static int[][] dirinfo;
	static int[] di = {0, -1, -1, -1, 0, 1, 1, 1};
	static int[] dj = {-1, -1, 0, 1, 1, 1, 0, -1};	
	static int nowdir;
	static int movelen;
	static int[][] nowcloud;
	static int size;
	static int dirsize;
	
	public static void main(String[] args) throws Exception{
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer ST = new StringTokenizer(br.readLine());
		
		size = Integer.parseInt(ST.nextToken());
		dirsize = Integer.parseInt(ST.nextToken());
		
		arr = new int[size+1][size+1];	//배열 
		dirinfo = new int[dirsize][2];	//이동정보
		nowcloud = new int[size+1][size+1];
		
		for(int i=1; i<=size; i++) {
			ST = new StringTokenizer(br.readLine());
			for(int j=1; j<=size; j++) {
				arr[i][j] = Integer.parseInt(ST.nextToken());
			}
		}
		
		for(int i=0; i<dirsize; i++) {
			ST = new StringTokenizer(br.readLine());
			for(int j=0; j<2; j++) {
				dirinfo[i][j] = Integer.parseInt(ST.nextToken());
			}
		}
		
		cloudsetting();
		
		for(int i=0; i<dirsize; i++) {
			nowdir = dirinfo[i][0]-1;
			movelen = dirinfo[i][1];
			
			cloudmove();
			//cloudprint();
			
			rain();
			//arrprint();
			
			magic();
			//arrprint();
			
			cloudmake();
			//cloudprint();
		}
		
		int cnt = 0;
		for(int i=1; i<=size; i++) {
			for(int j=1; j<=size; j++) {
				cnt+=arr[i][j];
			}
		}
		System.out.println(cnt);
	}
	
	static void arrprint() {
		for(int i=1; i<=size; i++) {
			for(int j=1; j<=size; j++) {
				System.out.print(arr[i][j]+" ");
			}
			System.out.println();
		}
		System.out.println();
	}
	
	static void cloudprint() {
		for(int i=1; i<=size; i++) {
			for(int j=1; j<=size; j++) {
				System.out.print(nowcloud[i][j]+" ");
			}
			System.out.println();
		}
		System.out.println();
	}
	
	static void cloudsetting() {
		nowcloud[size][1] = 1;
		nowcloud[size][2] = 1;
		nowcloud[size-1][1] = 1;
		nowcloud[size-1][2] = 1;
	}

	static void cloudmove() {
		ArrayList<int[]>nowlist = new ArrayList<>();	//원래있던 구름위치 리스트에 담기
		for(int i=1; i<=size; i++) {
			for(int j=1; j<=size; j++) {
				if(nowcloud[i][j]==1) {
					nowlist.add(new int[] {i,j});
					nowcloud[i][j] = 0;
				}
			}
		}
		
		ArrayList<int[]>newlist = new ArrayList<>();
		
		for(int i=0; i<nowlist.size(); i++) {			//이동 후 새로운 리스트에 담기 
			int[] now = nowlist.get(i);
			int nowi = now[0];	int nowj = now[1];
			
			int ni = nowi+di[nowdir]*movelen;
			int nj = nowj+dj[nowdir]*movelen;
			
			if(ni<0) {
				ni*=-1;
				ni%=size;
				ni*=-1;
				ni+=size;
			}else ni%=size;
			
			if(ni==0)ni+=size;
			
			if(nj<0) {
				nj*=-1;
				nj%=size;
				nj*=-1;
				nj+=size;
			}else nj%=size;
			
			if(nj==0)nj+=size;
			
			newlist.add(new int[] {ni, nj});
		}
		
		for(int i=0; i<newlist.size(); i++) {			//옮긴좌표 새로 구름 표시 
			int[] next = newlist.get(i);
			int ni = next[0];	int nj = next[1];
			nowcloud[ni][nj] = 1;
		}
	}
	
	static void rain() {								//비내리는곳에 1추가
		for(int i=1; i<=size; i++) {
			for(int j=1; j<=size; j++) {
				if(nowcloud[i][j]==1)arr[i][j]+=1;
			}
		}
	}
	
	static int cdi[] = {-1, -1, 1, 1};
	static int cdj[] = {-1, 1, 1, -1};
	
	static boolean check(int i, int j) {
		if(1<=i&&i<=size && 1<=j&&j<=size)return true;
		return false;
	}
	
	static void magic() {								//인접 대각선 4곳 체크 
		for(int i=1; i<=size; i++) {
			for(int j=1; j<=size; j++) {
				if(nowcloud[i][j]==1) {
					int cnt = 0;
					for(int d=0; d<4; d++) {
						int ni = i+cdi[d];
						int nj = j+cdj[d];
						if(check(ni, nj) && arr[ni][nj]>=1)cnt++;
					}
					arr[i][j]+=cnt;
				}
			}
		}
	}
	
	static void cloudmake() {
		ArrayList<int[]>nowlist = new ArrayList<>();
		for(int i=1; i<=size; i++) {
			for(int j=1; j<=size; j++) {
				if(nowcloud[i][j]==1) {
					nowlist.add(new int[] {i,j});
					nowcloud[i][j] = 0;
				}
			}
		}
		
		ArrayList<int[]>newlist = new ArrayList<>();
		for(int i=1; i<=size; i++) {
			for(int j=1; j<=size; j++) {
				if(arr[i][j]>=2)newlist.add(new int[] {i,j});
			}
		}
		
		for(int i=0; i<newlist.size(); i++) {
			int[] newcloud = newlist.get(i);
			int newi = newcloud[0];
			int newj = newcloud[1];
			
			int flag = 0;
			for(int j=0; j<nowlist.size(); j++) {
				int[] nowcloud = nowlist.get(j);
				int nowi = nowcloud[0];
				int nowj = nowcloud[1];
				if(newi==nowi && newj==nowj) {
					flag=1;
					break;
				}
			}
			if(flag == 0) {
				nowcloud[newi][newj] = 1;
				arr[newi][newj]-=2;
			}
		}
	}
}
