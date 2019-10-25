package com.pontoeletronico.controller.form;

import java.time.LocalDateTime;

import javax.validation.constraints.NotNull;

public class RegistroForm {

	@NotNull
	private String tagRFID;
	@NotNull
	private long tipo;
	@NotNull
	private LocalDateTime data;
	
	public String getTagRFID() {
		return tagRFID;
	}
	public void setTagRFID(String tagRFID) {
		this.tagRFID = tagRFID;
	}
	public long getTipo() {
		return tipo;
	}
	public void setTipo(long tipo) {
		this.tipo = tipo;
	}
	public LocalDateTime getData() {
		return data;
	}
	public void setData(LocalDateTime data) {
		this.data = data;
	}
	
}
