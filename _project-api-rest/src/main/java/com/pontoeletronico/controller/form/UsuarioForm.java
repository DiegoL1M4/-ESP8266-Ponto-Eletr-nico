package com.pontoeletronico.controller.form;

import javax.validation.constraints.NotEmpty;
import javax.validation.constraints.NotNull;

public class UsuarioForm {
	
	@NotNull @NotEmpty
	private String nome;
	@NotNull @NotEmpty
	private String tagRFID;
	
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

}
