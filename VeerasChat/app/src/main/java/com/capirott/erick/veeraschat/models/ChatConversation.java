package com.capirott.erick.veeraschat.models;

import java.util.ArrayList;
import java.util.Collection;

public class ChatConversation {

    private String id;

    private Collection<String> messagesId = new ArrayList<>();

    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }

    public Collection<String> getMessagesId() {
        return messagesId;
    }

    public void setMessagesId(Collection<String> messagesId) {
        this.messagesId = messagesId;
    }

    public void addMessageId(String messageId) {
        this.messagesId.add(messageId);
    }
}
