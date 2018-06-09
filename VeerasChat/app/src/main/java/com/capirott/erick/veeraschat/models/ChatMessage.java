package com.capirott.erick.veeraschat.models;

import java.util.Date;

public class ChatMessage {

    private String id;

    private String userId;

    private String text;

    private String imageBase64;

    private long time;

    public ChatMessage(String text, String userId) {
        this.text = text;
        this.userId = userId;
        this.time = new Date().getTime();
    }

    public String getId() {
        return id;
    }

    public ChatMessage(String userId) {
        this.userId = userId;
    }

    public ChatMessage() {
        return;
    }

    public String getUserId() {
        return userId;
    }

    public void setUserId(String userId) {
        this.userId = userId;
    }

    public String getText() {
        return text;
    }

    public void setText(String text) {
        this.text = text;
    }

    public String getImageBase64() {
        return imageBase64;
    }

    public void setImageBase64(String imageBase64) {
        this.imageBase64 = imageBase64;
    }

    public long getTime() {
        return time;
    }

    public void setTime(long time) {
        this.time = time;
    }
}
