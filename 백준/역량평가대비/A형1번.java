package a0315;

import java.util.*;
import java.io.*;

/*
 입력순서: 
 tc개수입력 
 낚시터 자리 갯수 -> 낚시터 출입구 3줄에 각각 위치, 대기인원
 ->tc만큼 반복
 
 구하는것 : 낚시꾼들의 이동거리 총합의 최소값 
 
 우선 낚시터 순서 3개 순열 돌리고 
 마지막 인원이 동일 위치가 나올때 위치선정을 어떻게 할것인가?
 -> 이부분을 dfs로 각각 나눠서 재귀처리?
 
 순서 1) 게이트 순서로 순열 생성 (총6개)
 순서 2) 규칙에 따라 해당게이트의 인원배치
 		 + 마지막인원이 경우의수 2개 가능할때 둘다 dfs로 처리  

 
 */


public class A형1번 {
	
	static int[] gateresult = new int[3];
	static int[][] gate;
	static int size;
	static int minmove = Integer.MAX_VALUE;		//최종결과값 
	static int move = 0;
	
	
	static int leftmyseat(int idx, int[] visit) {
		int nowidx = idx;
		//System.out.println(Arrays.toString(visit));
		for(int i=nowidx; i>=1; i--) {
			if(visit[i]==0)return i;		//gate에서 왼쪾으로 가장 가까운 자리
		}
		return -500;							//없을경우
	}
	
	static int rightmyseat(int idx, int[] visit) {
		int nowidx =idx;
		//System.out.println(Arrays.toString(visit));
		for(int i=nowidx; i<=size; i++) {
			if(visit[i]==0)return i;		//gate에서 오른쪽으로 가장 가까운 자리
		}
		return 500;	
	}
	
	static void minfind(int cnt, int[] visit, int move) {			//결정된 gate순열로 자리배치해보기
		
//		System.out.println("gatecnt:"+cnt);
		//System.out.println(Arrays.toString(visit));
		//System.out.println("cnt:"+cnt+" move:"+move);
		
		if(cnt==3) {
			minmove = Math.min(move, minmove);
			//System.out.println("minmove:"+minmove);
//			System.out.println();
			return;
		}
		
		int nowgateidx = gateresult[cnt];
		int nowgate = gate[nowgateidx][0];			//현재 gate의 idx
		int waitnum = gate[nowgateidx][1];			// 이 게이트에서 기다리는 사람 수
		int findidx = nowgate;
		int nowmovesum = 0;
		
		for(int i=0; i<waitnum; i++) {				//현재 게이트에서 자리배치
			
			
			int leftidx = leftmyseat(findidx, visit);
			int rightidx = rightmyseat(findidx, visit);
			
//			System.out.println("nowgate:"+nowgate);
//			System.out.println("cnt:"+cnt+" i:"+i+" leftidx:"+leftidx+" rightidx:"+rightidx);
//			System.out.println(Arrays.toString(visit));
			
			
			if(i!=waitnum-1){			//마지막 아닐때
				if(nowgate-leftidx > rightidx-nowgate) {	//오른쪽이 더 가까울때
					visit[rightidx] = 1;
					nowmovesum+=rightidx-nowgate+1;
				}else if(nowgate-leftidx < rightidx-nowgate) {	//왼쪾이 더가까울때
					visit[leftidx] = 1;
					nowmovesum+=nowgate-leftidx+1;
				}else {				// 같을때
					visit[leftidx] = 1;
					nowmovesum+=nowgate-leftidx+1;
				}
//				System.out.println(Arrays.toString(visit));
//				System.out.println(nowmovesum);
			}else {					//마지막 일때
				if(nowgate-leftidx > rightidx-nowgate) {	//오른쪽이 더 가까울때
					visit[rightidx] = 1;
					nowmovesum+=rightidx-nowgate+1;
//					System.out.println(nowmovesum);
//					System.out.println(Arrays.toString(visit));
//					System.out.println();
					minfind(cnt+1, visit, move+nowmovesum);
				}else if(nowgate-leftidx < rightidx-nowgate) {	//왼쪾이 더가까울때
					visit[leftidx] = 1;
					nowmovesum+=nowgate-leftidx+1;
//					System.out.println(nowmovesum);
//					System.out.println(Arrays.toString(visit));
//					System.out.println();
					minfind(cnt+1, visit, move+nowmovesum);
				}else {				// 같을때
					int tmp1[] = new int[size+1];
					int tmp2[] = new int[size+1];
					for(int k=1; k<=size; k++) {
						tmp1[k] = visit[k];
						tmp2[k] = visit[k];
					}
					
					tmp1[leftidx] = 1;
					nowmovesum+=nowgate-leftidx+1;
//					System.out.println("야호0");
//					//System.out.println(nowmovesum);
//					System.out.println(Arrays.toString(tmp1));
//					System.out.println();
					minfind(cnt+1, tmp1, move+nowmovesum);
					nowmovesum-=nowgate-leftidx+1;
					
//					System.out.println(Arrays.toString(tmp2));
//					System.out.println();
					//System.out.println("야호1");
					tmp2[rightidx] = 1;
					nowmovesum+=rightidx-nowgate+1;
					//System.out.println(nowmovesum);
//					System.out.println(Arrays.toString(tmp2));
//					System.out.println();
					minfind(cnt+1, tmp2, move+nowmovesum);
					//System.out.println("야호2");
					
				}
			}
			//System.out.println(Arrays.toString(visit));
			//System.out.println();
		}
		
	}
	
	static int[] gatevisit = new int[3];
	
	
	static void gatepowerset(int cnt) {			//gate 순열 생성
		
		if(cnt==3) {
			int visit[] = new int[size+1];
//			System.out.println("Gate idx순열돌리기");
//			System.out.println(Arrays.toString(gateresult));
		
			minfind(0, visit, 0);
			return;
		}
		
		for(int i=0; i<3; i++) {
			if(gatevisit[i]==0) {			//방문 안한수 처리
				gatevisit[i] = 1;
				gateresult[cnt] = i;		//gate 2차원배열의 idx저장
				gatepowerset(cnt+1);
				gatevisit[i] = 0;
			}
		}
	}
	
	
	public static void main(String[] args) throws Exception{
		
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		int tc = Integer.parseInt(br.readLine());
		gate = new int[3][2];
		
		for(int t=1; t<=tc; t++) {
			
			size = Integer.parseInt(br.readLine());
	
			for(int i=0; i<3; i++) {
				StringTokenizer ST = new StringTokenizer(br.readLine());
				int gateidx = Integer.parseInt(ST.nextToken());
				int waitnum = Integer.parseInt(ST.nextToken());
				
				gate[i][0] = gateidx;
				gate[i][1] = waitnum;
			}
			
			//------------입력완료-----------//
			minmove = Integer.MAX_VALUE;
			gatepowerset(0);
			
			System.out.println("#"+t+" "+minmove);
		}
	}

}
