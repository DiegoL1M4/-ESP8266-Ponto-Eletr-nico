package com.pontoeletronico.entities;

import java.time.LocalDateTime;

import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;

@Entity
public class Usuario {

	@Id @GeneratedValue(strategy = GenerationType.IDENTITY)
	private int id_usuario;
	private String nome;
	private String tagRFID;
	private LocalDateTime data;
	
	public Usuario() { }
	
	public Usuario(String nome, String tagRFID) {
		this.nome = nome;
		this.tagRFID = tagRFID;
		this.data = LocalDateTime.now();
	}
	
	public int getId_usuario() {
		return id_usuario;
	}
	public void setId_usuario(int id_usuario) {
		this.id_usuario = id_usuario;
	}
	public String getNome() {
		return nome;
	}
	public void setNome(String nome) {
		this.nome = nome;
	}
	public String getTagRFID() {
		return tagRFID;
	}
	public void setTagRFID(String tagRFID) {
		this.tagRFID = tagRFID;
	}
	public LocalDateTime getData() {
		return data;
	}
	public void setData(LocalDateTime data) {
		this.data = data;
	}

}
