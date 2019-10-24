package com.pontoeletronico.controller.form;

import java.time.LocalDateTime;

import javax.validation.constraints.NotNull;

public class RegistroForm {

	@NotNull
	private String tagRFID;
	@NotNull
	private LocalDateTime data;
	
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
