package com.capirott.erick.veeraschat.models;

import java.util.Date;

public class ChatMessage {

    private String userId;

    private String text;

    private long messageTime;

    public ChatMessage(String text, String userId) {
        this.userId = userId;
        this.text = text;

        // Initialize to current time
        messageTime = new Date().getTime();
    }

    public ChatMessage(){

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

    public long getMessageTime() {
        return messageTime;
    }

    public void setMessageTime(long messageTime) {
        this.messageTime = messageTime;
    }
}
