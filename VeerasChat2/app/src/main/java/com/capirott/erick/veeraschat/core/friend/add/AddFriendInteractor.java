package com.capirott.erick.veeraschat.core.friend.add;

import android.content.Context;
import android.support.annotation.NonNull;

import com.capirott.erick.veeraschat.R;
import com.capirott.erick.veeraschat.models.User;
import com.capirott.erick.veeraschat.utils.Constants;
import com.capirott.erick.veeraschat.utils.SharedPrefUtil;
import com.google.android.gms.tasks.OnCompleteListener;
import com.google.android.gms.tasks.Task;
import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;


public class AddFriendInteractor implements AddFriendContract.Interactor {
    private AddFriendContract.OnFriendDatabaseListener mOnFriendDatabaseListener;

    public AddFriendInteractor(AddFriendContract.OnFriendDatabaseListener onFriendDatabaseListener) {
        this.mOnFriendDatabaseListener = onFriendDatabaseListener;
    }

    @Override
    public void addFriendToDatabase(final Context context, final User user) {
    }

}
