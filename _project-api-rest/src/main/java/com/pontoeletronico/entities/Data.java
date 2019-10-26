package com.pontoeletronico.entities;

public class Data {
	
	private int h;
	private int m;
	private int s;
	private int wk;
	private int d;
	private int mth;
	private int a;
	
	public Data(int h, int m, int s, int wk, int d, int mth, int a) {
		this.h = h;
		this.m = m;
		this.s = s;
		this.wk = wk;
		this.d = d;
		this.mth = mth;
		this.a = a;
	}

	public int getH() {
		return h;
	}

	public void setH(int h) {
		this.h = h;
	}

	public int getM() {
		return m;
	}

	public void setM(int m) {
		this.m = m;
	}

	public int getS() {
		return s;
	}

	public void setS(int s) {
		this.s = s;
	}

	public int getWk() {
		return wk;
	}

	public void setWk(int wk) {
		this.wk = wk;
	}

	public int getD() {
		return d;
	}

	public void setD(int d) {
		this.d = d;
	}

	public int getMth() {
		return mth;
	}

	public void setMth(int mth) {
		this.mth = mth;
	}

	public int getA() {
		return a;
	}

	public void setA(int a) {
		this.a = a;
	}
	
}
