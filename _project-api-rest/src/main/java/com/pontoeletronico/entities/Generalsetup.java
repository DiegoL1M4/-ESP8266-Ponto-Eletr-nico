package com.pontoeletronico.entities;

import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;

@Entity
public class Generalsetup {
	
	@Id @GeneratedValue(strategy = GenerationType.IDENTITY)
	private Long id_setup;
	private String nome;
	private String valor;
	
	public Generalsetup() { }
	
	public Generalsetup(String nome, String valor) {
		this.nome = nome;
		this.valor = valor;
	}
	
	public Long getId_setup() {
		return id_setup;
	}
	public void setId_setup(Long id_setup) {
		this.id_setup = id_setup;
	}
	public String getNome() {
		return nome;
	}
	public void setNome(String nome) {
		this.nome = nome;
	}
	public String getValor() {
		return valor;
	}
	public void setValor(String valor) {
		this.valor = valor;
	}

}
