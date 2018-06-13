package com.capirott.erick.veeraschat.ui.activities;

import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.os.Bundle;
import android.support.v4.app.FragmentTransaction;
import android.support.v7.app.AlertDialog;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.Toast;

import com.capirott.erick.veeraschat.FirebaseChatMainApp;
import com.capirott.erick.veeraschat.R;
import com.capirott.erick.veeraschat.core.friend.add.AddFriendContract;
import com.capirott.erick.veeraschat.core.friend.add.AddFriendPresenter;
import com.capirott.erick.veeraschat.core.friend.get.GetFriendContract;
import com.capirott.erick.veeraschat.core.friend.get.GetFriendPresenter;
import com.capirott.erick.veeraschat.core.users.get.all.GetUsersContract;
import com.capirott.erick.veeraschat.models.User;
import com.capirott.erick.veeraschat.ui.fragments.ChatFragment;
import com.capirott.erick.veeraschat.utils.Constants;
import com.google.firebase.auth.FirebaseAuth;
import com.google.firebase.auth.FirebaseUser;

public class ChatActivity extends AppCompatActivity implements AddFriendContract.View,GetFriendContract.View {

    private Toolbar mToolbar;

    private AddFriendPresenter mAddFriendPresenter;

    private GetFriendPresenter mGetFriendPresenter;

    private User user;

    private MenuItem addFriendItem;

    public static void startActivity(Context context, User user) {
        Intent intent = new Intent(context, ChatActivity.class);
        intent.putExtra(Constants.ARG_USER_RECEIVER, user);
        context.startActivity(intent);
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {
            case R.id.action_add_friend:
                addFriend();
                break;
        }
        return super.onOptionsItemSelected(item);
    }

    private void addFriend() {
        new AlertDialog.Builder(this)
                .setTitle(R.string.new_friend)
                .setMessage(R.string.are_you_sure)
                .setPositiveButton(R.string.add_friend, new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        dialog.dismiss();
                        Log.d("ChatActivity", "friendShipExists: " + user.getNickname());
                        mAddFriendPresenter.addFriend(getBaseContext(), FirebaseAuth.getInstance().getCurrentUser().getUid(), user.getUid());
                    }
                })
                .setNegativeButton(R.string.cancel, new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        dialog.dismiss();
                    }
                })
                .show();
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.menu_chat_listing, menu);
        addFriendItem = menu.findItem(R.id.action_add_friend);
        addFriendItem.setVisible(false);
        if (FirebaseAuth.getInstance().getCurrentUser().isAnonymous()) {
            Log.d("ChatActivity", "onCreateOptionsMenu: you are not registered!");
        } else if (user.getEmail() == null) {
            Log.d("ChatActivity", "onCreateOptionsMenu: " + user.getNickname() + " is not registered!");
        } else {
            Log.d("ChatActivity", "onCreateOptionsMenu: " + user.getNickname() + " is registered!");
            mGetFriendPresenter.friendShipExists(getBaseContext(), FirebaseAuth.getInstance().getCurrentUser().getUid(), user.getUid());
        }
        return super.onCreateOptionsMenu(menu);
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        user = (User) getIntent().getSerializableExtra(Constants.ARG_USER_RECEIVER);
        setContentView(R.layout.activity_chat);
        bindViews();
        init();
    }

    private void bindViews() {
        mToolbar = (Toolbar) findViewById(R.id.toolbar);
    }

    private void init() {
        // set the toolbar
        setSupportActionBar(mToolbar);

        mAddFriendPresenter = new AddFriendPresenter(this);
        mGetFriendPresenter = new GetFriendPresenter(this);

        // set toolbar title
        mToolbar.setTitle(user.getNickname());

        // set the register screen fragment
        FragmentTransaction fragmentTransaction = getSupportFragmentManager().beginTransaction();
        fragmentTransaction.replace(R.id.frame_layout_content_chat,
                ChatFragment.newInstance(user), ChatFragment.class.getSimpleName());
        fragmentTransaction.commit();
    }

    @Override
    protected void onResume() {
        super.onResume();
        FirebaseChatMainApp.setChatActivityOpen(true);
    }

    @Override
    public void onBackPressed() {
        super.onBackPressed();
        if (isTaskRoot()) {
            UserListingActivity.startActivity(getBaseContext());
            finish();
        }
    }

    @Override
    protected void onPause() {
        super.onPause();
        FirebaseChatMainApp.setChatActivityOpen(false);
    }

    @Override
    public void onAddFriendSuccess(String message) {
        addFriendItem.setVisible(false);
        Toast.makeText(this, message, Toast.LENGTH_SHORT).show();
    }

    @Override
    public void onAddFriendFailure(String message) {
        Toast.makeText(this, message, Toast.LENGTH_SHORT).show();
    }

    @Override
    public void onGetFriendSuccess(String message) {
        addFriendItem.setVisible(false);
    }

    @Override
    public void onGetFriendFailure(String message) {
        addFriendItem.setVisible(true);
    }
}
