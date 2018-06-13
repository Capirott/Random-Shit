package com.capirott.erick.veeraschat.core.friend.add;

import android.content.Context;
import android.util.Log;

import com.capirott.erick.veeraschat.R;
import com.capirott.erick.veeraschat.utils.Constants;
import com.capirott.erick.veeraschat.utils.SharedPrefUtil;
import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;


public class AddFriendInteractor implements AddFriendContract.Interactor {

    private static final String TAG = "GetFriendInteractor";

    private AddFriendContract.OnFriendDatabaseListener mOnFriendDatabaseListener;


    public AddFriendInteractor(AddFriendContract.OnFriendDatabaseListener onFriendDatabaseListener) {
        this.mOnFriendDatabaseListener = onFriendDatabaseListener;
    }

    @Override
    public void addFriendToDatabase(final Context context, final String userId, final String userId2) {
        final DatabaseReference databaseReference = FirebaseDatabase.getInstance().getReference();

        databaseReference.child(Constants.ARG_USERS).getRef().addListenerForSingleValueEvent(new ValueEventListener() {
            @Override
            public void onDataChange(DataSnapshot dataSnapshot) {

                dataSnapshot.child(userId).child(Constants.ARG_FRIENDS).child(userId2).getRef().setValue(true);
                Log.d(TAG, "friendShipExists: success");
                mOnFriendDatabaseListener.onSuccess(context.getString(R.string.friend_successfully_added));
            }

            @Override
            public void onCancelled(DatabaseError databaseError) {
                mOnFriendDatabaseListener.onFailure("Unable to add friend message: " + databaseError.getMessage());
            }
        });
    }

}
