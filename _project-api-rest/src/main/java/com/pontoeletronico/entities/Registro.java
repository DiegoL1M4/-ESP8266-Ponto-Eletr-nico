package com.pontoeletronico.entities;

import java.time.LocalDateTime;

import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;

@Entity
public class Registro {

	@Id @GeneratedValue(strategy = GenerationType.IDENTITY)
	private int id_registro;
	private String tagRFID;
	private int tipo;
	private LocalDateTime data;
	
	public Registro() { }
	
	public Registro(String tagRFID, int tipo, LocalDateTime data) {
		this.tagRFID = tagRFID;
		this.tipo = tipo;
		this.data = data;
		System.out.println(data);
	}

	public String getTagRFID() {
		return tagRFID;
	}

	public void setTagRFID(String tagRFID) {
		this.tagRFID = tagRFID;
	}

	public int getId_registro() {
		return id_registro;
	}
	public void setId_registro(int id_registro) {
		this.id_registro = id_registro;
	}
	public int getTipo() {
		return tipo;
	}
	public void setTipo(int tipo) {
		this.tipo = tipo;
	}
	public LocalDateTime getData() {
		return data;
	}
	public void setData(LocalDateTime data) {
		this.data = data;
	}
	
}
