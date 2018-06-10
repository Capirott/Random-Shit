package com.capirott.erick.veeraschat.managers;

import android.app.Activity;
import android.util.Log;
import android.view.View;
import android.widget.ListAdapter;
import android.widget.TextView;

import com.capirott.erick.veeraschat.R;
import com.capirott.erick.veeraschat.models.ChatUser;
import com.firebase.ui.database.FirebaseListAdapter;
import com.google.firebase.auth.FirebaseAuth;
import com.google.firebase.auth.FirebaseUser;
import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;

import java.util.ArrayList;
import java.util.List;

public class ChatUserManager {

    private static final String FIREBASE_REFERENCE = "USERS";

    static public void save(ChatUser user) {
        FirebaseDatabase.getInstance()
                .getReference(FIREBASE_REFERENCE)
                .push()
                .setValue(user
                );

    }

    static public ListAdapter getAdapter(Activity activity) {
        DatabaseReference databaseReference = FirebaseDatabase.getInstance().getReference(FIREBASE_REFERENCE);
        FirebaseListAdapter<ChatUser> adapter = new FirebaseListAdapter<ChatUser>(activity, ChatUser.class,
                R.layout.random, databaseReference) {
            @Override
            protected void populateView(View v, ChatUser model, int position) {
                TextView userName = (TextView) v.findViewById(R.id.random_user_name);
                userName.setText("Anon#" + String.format("%04d", position));
            }
        };
        return adapter;
    }

    static public void createOrUpdate(final String id, final boolean isOnline) {
        createOrUpdate(id, isOnline, null);
    }

    static public void createOrUpdate(final String id, final boolean isOnline, final Runnable callback) {
        final List<ChatUser> events = new ArrayList<>();
        DatabaseReference ref = FirebaseDatabase.getInstance().getReference(FIREBASE_REFERENCE);
        ref.addListenerForSingleValueEvent(new ValueEventListener() {
            @Override
            public void onDataChange(DataSnapshot dataSnapshot) {
                Log.d("ChatUserManager", "onDataChange");
                DataSnapshot theOne = null;
                int pos = 0;
                for (DataSnapshot snapshot : dataSnapshot.getChildren()) {
                    pos++;
                    ChatUser event = snapshot.getValue(ChatUser.class);
                    if (event.getId().equals(id)) {
                        Log.d("ChatUserManager", "Found user!");
                        events.add(event);
                        theOne = snapshot;
                    }
                }
                ChatUser chatUser = new ChatUser();
                if (theOne != null) {
                    theOne.child("online").getRef().setValue(isOnline);
                    Log.d("ChatUserManager", "User Online set to " + isOnline);
                } else {
                    FirebaseUser currentUser = FirebaseAuth.getInstance().getCurrentUser();
                    chatUser.setNickname("Anon#" + String.format("%04d", pos));
                    chatUser.setOnline(isOnline);
                    chatUser.setId(currentUser.getUid());
                    ChatUserManager.save(chatUser);
                    Log.d("ChatUserManager", "User created!");
                }
                if (callback != null) {
                    callback.run();
                }
            }
            @Override
            public void onCancelled(DatabaseError databaseError) {

            }
        });
    }
}
