package com.capirott.erick.veeraschat.core.friend.get.all;

import android.provider.ContactsContract;

import com.capirott.erick.veeraschat.models.User;
import com.capirott.erick.veeraschat.utils.Constants;
import com.google.firebase.database.ChildEventListener;
import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;
import java.util.concurrent.atomic.AtomicLong;


public class GetFriendsInteractor implements GetFriendsContract.Interactor {
    private static final String TAG = "GetUsersInteractor";

    private GetFriendsContract.OnGetAllFriendsListener mOnGetAllFriendsListener;

    public GetFriendsInteractor(GetFriendsContract.OnGetAllFriendsListener onGetAllFriendsListener) {
        this.mOnGetAllFriendsListener = onGetAllFriendsListener;
    }


    @Override
    public void getAllFriendsFromFirebase(final String userId) {
        final List<User> users = new ArrayList<>();
        final DatabaseReference userRefDb = FirebaseDatabase.getInstance().getReference().child(Constants.ARG_USERS);
        userRefDb.child(userId).child(Constants.ARG_FRIENDS).addListenerForSingleValueEvent(new ValueEventListener() {
            @Override
            public void onDataChange(DataSnapshot dataSnapshot) {
                if (dataSnapshot.getValue() != null) {
                    final AtomicLong count = new AtomicLong(dataSnapshot.getChildrenCount());
                    dataSnapshot.getRef().addListenerForSingleValueEvent(new ValueEventListener() {
                        @Override
                        public void onDataChange(DataSnapshot dataSnapshot) {
                            for (DataSnapshot child : dataSnapshot.getChildren()) {
                                String userId = child.getKey();
                                if (child.getValue(Boolean.class)) {
                                    userRefDb.child(userId).addListenerForSingleValueEvent(new ValueEventListener() {
                                        @Override
                                        public void onDataChange(DataSnapshot dataSnapshot) {
                                            users.add(dataSnapshot.getValue(User.class));
                                            if (count.decrementAndGet() == 0) {
                                                mOnGetAllFriendsListener.onGetAllFriendsSuccess(users);
                                                Collections.sort(users, new Comparator<User>() {
                                                    @Override
                                                    public int compare(User user, User t1) {
                                                        return user.getNickname().compareTo(t1.getNickname());
                                                    }
                                                });
                                            }
                                        }

                                        @Override
                                        public void onCancelled(DatabaseError databaseError) {
                                            mOnGetAllFriendsListener.onGetAllFriendsFailure(databaseError.getMessage());
                                        }
                                    });
                                } else {
                                    if (count.decrementAndGet() == 0) {
                                        mOnGetAllFriendsListener.onGetAllFriendsSuccess(users);
                                    }
                                }
                            }
                        }

                        @Override
                        public void onCancelled(DatabaseError databaseError) {

                        }
                    });

                } else {
                    mOnGetAllFriendsListener.onGetAllFriendsSuccess(users);
                }
            }

            @Override
            public void onCancelled(DatabaseError databaseError) {
                mOnGetAllFriendsListener.onGetAllFriendsFailure(databaseError.getMessage());
            }
        });
    }
}
